#include "controlador_juego.h"
#include "../app/recursos.h"

using namespace App_Niveles;
using namespace App_Juego;
using namespace App_Graficos;
using namespace App_Colisiones;
using namespace App_Input;

/**
* TODO: Notas para el generador de salas:
* - Cada sala tendría que tener un spawn point además de sus salidas.
* - El algoritmo podría decir "voy a generar 4 salas de camino y luego 3 extras".
* - Generaría el camino y luego, de entre lo que sobre, colocaría las extras.
* - Al colocar las salas secuenciales determina las salidas que tiene.
* - Al colocar las salas extras determina las salidas que tienen.
* - No queda claro al colocar una extra a qué sala estaría conectada: si 
* elegimos una al azar entre las adyacentes y sólo una no habrá loops en los 
* mapas. Algo interesante sería asignar a la única posible (si la hay) y si hay
* más de una asignar oportunidades distintas a cada una.
* - El algoritmo no detecta dead ends para darles buenas cosas. Se podría 
* calcular la distancia a las salas que tienen una única salida con respecto
* al inicio para darles unos niveles de bonus o algo. Con respecto a la salida
* o a la llegada, que son los sitios obligatorios a los que hay que ir. Si 
* lo hacemos así tendremos que meternos en pathfinding para no andar en 
* círculos!!!!!
*/

Controlador_juego::Controlador_juego(Director_estados &DI, DLibV::Pantalla& pantalla)
	:Controlador_base(DI),
	mapa(2, 2),
	jugador(32.0, 32.0),
	sala_actual(nullptr)
{

	Sala sala0_0(20, 10, 0, 0);
	Sala sala1_0(20, 10, 1, 0);
	Sala sala0_1(20, 10, 0, 1);
	Sala sala1_1(20, 10, 1, 1);

	for(unsigned int x=0; x<sala0_0.acc_w(); ++x)
	{
		sala0_0.insertar_celda(x, 0, Celda::tipo_celda::solida);
		sala0_0.insertar_celda(x, 9, Celda::tipo_celda::solida);
		sala1_0.insertar_celda(x, 0, Celda::tipo_celda::solida);
		sala1_0.insertar_celda(x, 9, Celda::tipo_celda::solida);
		sala0_1.insertar_celda(x, 0, Celda::tipo_celda::solida);
		sala0_1.insertar_celda(x, 9, Celda::tipo_celda::solida);
		sala1_1.insertar_celda(x, 0, Celda::tipo_celda::solida);
		sala1_1.insertar_celda(x, 9, Celda::tipo_celda::solida);
	}

	for(unsigned int y=1; y<sala0_0.acc_h()-1; ++y)
	{
		sala0_0.insertar_celda(0, y, Celda::tipo_celda::solida);
		sala0_0.insertar_celda(19, y, Celda::tipo_celda::solida);
		sala1_0.insertar_celda(0, y, Celda::tipo_celda::solida);
		sala1_0.insertar_celda(19, y, Celda::tipo_celda::solida);
		sala0_1.insertar_celda(0, y, Celda::tipo_celda::solida);
		sala0_1.insertar_celda(19, y, Celda::tipo_celda::solida);
		sala1_1.insertar_celda(0, y, Celda::tipo_celda::solida);
		sala1_1.insertar_celda(19, y, Celda::tipo_celda::solida);
	}

	sala0_0.erase(19, 5);
	sala0_0.erase(19, 6);
	sala0_0.erase(10, 9);
	sala0_0.erase(9, 9);

	sala1_0.erase(0, 5);
	sala1_0.erase(0, 6);
	sala1_0.erase(10, 9);
	sala1_0.erase(9, 9);

	sala0_1.erase(19, 5);
	sala0_1.erase(19, 6);
	sala0_1.erase(10, 0);
	sala0_1.erase(9, 0);

	sala1_1.erase(0, 5);
	sala1_1.erase(0, 6);
	sala1_1.erase(10, 0);
	sala1_1.erase(9, 0);
	
	mapa.insertar_sala(0,0,sala0_0);
	mapa.insertar_sala(1,0,sala1_0);
	mapa.insertar_sala(0,1,sala0_1);
	mapa.insertar_sala(1,1,sala1_1);
	

	sala_actual=&(mapa.obtener_sala(0, 0));
}

Controlador_juego::~Controlador_juego()
{
}

void Controlador_juego::preloop(Input_base& input, float delta)
{

}

void Controlador_juego::postloop(Input_base& input, float delta)
{

}

void Controlador_juego::loop(Input_base& input, float delta)
{
	if(input.es_senal_salida() || input.es_input_down(Input::I_ESCAPE))
	{
		abandonar_aplicacion();
	}
	else
	{
//		if(input.es_input_down(Input::I_ESPACIO))
//		{
//			solicitar_cambio_estado(Director_estados::t_estados::EJEMPLO);
//		}

		Recogedor_input RI;
		Input_usuario iu=RI.recoger_input_usuario(input);

		procesar_jugador(jugador, delta, iu);

		//TODO TODO TODO...
		if(jugador.acc_salud() <= 0.0)
		{
			abandonar_aplicacion();
		}
	
		controlar_salida_sala(jugador);
	}
}

/**
* @param Jugador j
*
* TODO: Ajustar coordenadas para que sea menos instantáneo.
* TODO: Colocar al jugador en una de las salidas.
* Controla que el jugador ha salido de una sala.
*/

void Controlador_juego::controlar_salida_sala(Jugador& j)
{
	int salida=0;

	if(j.acc_espaciable_x() < 0) salida=1;
	else if(j.acc_espaciable_x() > 630) salida=2;
	else if(j.acc_espaciable_y() < 0) salida=3;
	else if(j.acc_espaciable_y() > 360) salida=4;

	if(salida)
 	{
		int ax=sala_actual->acc_x(), ay=sala_actual->acc_y();
		switch(salida)
		{
			case 1: --ax; break;
			case 2: ++ax; break;
			case 3: --ay; break;
			case 4: ++ay; break;
		}
		j.colocar_inicio();
		sala_actual=&mapa.obtener_sala(ax, ay);
	}
}

/**
* @param Jugador& : El objeto del tipo Jugador sobre el que se actúa.
* @param float : El tiempo delta.
*/

void Controlador_juego::procesar_jugador(Jugador& j, float delta, Input_usuario iu)
{
	j.recoger_input(iu);
	j.turno(delta);
	j.accion_gravedad(delta, 1.0);

	auto v=j.acc_vector();
	if(v.y) 
	{
		jugador.desplazar_caja(0.0, v.y * delta);		
		Calculador_colisiones CC;
		std::vector<const Celda *> celdas=CC.celdas_en_caja(jugador.copia_caja(), *sala_actual);
		if(celdas.size()) CC.ajustar_colisiones_actor_movil_y_con_celdas(jugador, celdas);
	}

	if(v.x) 
	{
		jugador.desplazar_caja(v.x * delta, 0.0);
		Calculador_colisiones CC;
		std::vector<const Celda *> celdas=CC.celdas_en_caja(jugador.copia_caja(), *sala_actual);
		if(celdas.size()) CC.ajustar_colisiones_actor_movil_x_con_celdas(jugador, celdas);
	}
}

/**
* @param Pantalla& pantalla : La pantalla sobre la que se dibuja.
*/

void Controlador_juego::dibujar(DLibV::Pantalla& pantalla)
{
	pantalla.limpiar(128, 128, 128, 255);
	std::vector<const Representable *> vr=(*sala_actual).obtener_vector_celdas_representables();
	vr.push_back(&jugador);
	representador.generar_vista(pantalla, vr);

	std::stringstream ss;
	ss<<jugador.acc_espaciable_x()<<","<<jugador.acc_espaciable_y()<<" HULL: "<<jugador.acc_salud()<<" SHIELD: "<<jugador.acc_escudo();

	DLibV::Representacion_texto_auto_estatica rep_hud(pantalla.acc_renderer(), DLibV::Gestor_superficies::obtener(App::Recursos_graficos::RS_FUENTE_BASE), ss.str());
	rep_hud.establecer_posicion(16, 16);
	rep_hud.volcar(pantalla);
	

}
