#include <algorithm>

#include "controlador_juego.h"
#include "../app/recursos.h"
#include "../app/definiciones/definiciones.h"
#include "../app/generador/traductor_mapas.h"
#include "../app/generador/generador_estructura_niveles.h"

#include "../app/visitantes/visitante_objeto_juego.h"
#include "../app/juego/objetos_juego/bonus_tiempo.h"
#include "../app/juego/objetos_juego/bonus_salud.h"
#include "../app/juego/logica_bonus.h"
#include "../app/juego/logica_disparador.h"
#include "../app/juego/logica_con_turno.h"
#include "../app/juego/logica_disparable.h"
#include "../app/juego/logica_colisionable.h"

using namespace App_Niveles;
using namespace App_Juego;
using namespace App_Graficos;
using namespace App_Colisiones;
using namespace App_Input;

Controlador_juego::Controlador_juego(Director_estados &DI, DLibV::Pantalla& pantalla)
	:Controlador_base(DI),
	mapa(0, 0),
	jugador(32.0, 32.0),
	contador_tiempo(),
	sala_actual(nullptr)
{
	//TODO: Envolver todo esto en una clase que lo haga sólo...
	//TODO: Hacerlo cuando todo esté listo, claro.

	using namespace App_Generador;
	Generador_estructura_niveles GEN;
	GEN.generar_camino_principal(20);
	GEN.generar_salas_secundarias(20);
	GEN.normalizar();

	Traductor_mapas TM;
	mapa=TM.traducir_mapa(GEN.acc_proto_salas());

	sala_actual=&(mapa.obtener_sala_inicio());

	iniciar_automapa();

	const auto& pi=sala_actual->obtener_posicion_inicial_jugador();
	jugador.establecer_posicion(pi.acc_espaciable_x(), pi.acc_espaciable_y());

	contador_tiempo.mut_tiempo_restante(180.0);
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
		contador_tiempo.turno(delta);

		Recogedor_input RI;
		Input_usuario iu=RI.recoger_input_usuario(input);

		procesar_jugador(jugador, delta, iu);

		//TODO: Agrupar bajo condicion game over única.
		//TODO TODO TODO...
		if(jugador.acc_salud() <= 0.0)
		{
			abandonar_aplicacion();
		}

		//TODO TODO TODO...
		if(!contador_tiempo.es_tiempo_restante())
		{
			abandonar_aplicacion();
		}
	
		controlar_y_efectuar_salida_sala(jugador);

		logica_proyectiles(delta);
		logica_mundo(delta);
	}
}

/**
* @param Jugador j
* @return bool : true si se ha efectuado una salida.
* TODO: Ajustar coordenadas para que sea menos instantáneo.
*/

bool Controlador_juego::controlar_y_efectuar_salida_sala(Jugador& j)
{
	using namespace App_Definiciones;

	direcciones salida=direcciones::nada;

	if(j.acc_espaciable_x() < 0) salida=direcciones::izquierda;
	else if(j.acc_espaciable_x() > 630) salida=direcciones::derecha;
	else if(j.acc_espaciable_y() < 0) salida=direcciones::arriba;
	else if(j.acc_espaciable_y() > 320) salida=direcciones::abajo;

	if(salida!=direcciones::nada)
 	{
		int ax=sala_actual->acc_x(), ay=sala_actual->acc_y();
		switch(salida)
		{
			case direcciones::izquierda: --ax; break;
			case direcciones::derecha: ++ax; break;
			case direcciones::arriba: --ay; break;
			case direcciones::abajo: ++ay; break;
			case direcciones::nada: break;
		}

		cargar_sala(ax, ay, salida, j);
		return true;
	}
	
	return false;
}

/**
* @param int ax : Coordenada x de la sala en el nivel.
* @param int ay : Coordenada y de la sala en el nivel.
* @param direcciones : Dirección de la salida que el jugador ha tomado.
* @param Jugador : Jugador al que colocamos en la salida.
*/

void Controlador_juego::cargar_sala(int ax, int ay, App_Definiciones::direcciones salida, Jugador& j)
{
	try
	{
		limpiar_pre_cambio_sala();

		//TODO: Revisar si esto lanza y se está comprobando.
		sala_actual=&mapa.obtener_sala(ax, ay);

		//TODO: Revisar si esto lanza y se está comprobando.
		const auto& entrada=sala_actual->obtener_entrada_posicion(obtener_direccion_contraria(salida));
		j.establecer_en_posicion(entrada);
		refrescar_automapa();
	}
	catch(std::logic_error& e)
	{
		LOG<<"ERROR AL CAMBIAR DE SALA: "<<e.what()<<std::endl;
		abandonar_aplicacion();
	}
}

/**
* Ejecuta todos los procesos de limpieza que sean necesarios antes de abandonar
* una sala.
*/

void Controlador_juego::limpiar_pre_cambio_sala()
{
	proyectiles_jugador.clear();
}

/**
* @param Jugador& : El objeto del tipo Jugador sobre el que se actúa.
* @param float : El tiempo delta.
*/

void Controlador_juego::procesar_jugador(Jugador& j, float delta, Input_usuario iu)
{
	if(iu.usar)
	{
		if(jugador.disparar())
		{
			Logica_disparador lp(proyectiles_enemigos, jugador);
			lp.insertar_disparo_jugador(proyectiles_jugador);
		}
	}

	j.recoger_input(iu);
	j.turno(delta);

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

	//Las colisiones con objetos de juego se evaluan en la posición final.

	//En primer lugar evaluamos los bonus que se pueden recoger.

	Logica_bonus lb(contador_tiempo, jugador);
	sala_actual->procesar_bonus(lb);

	//Ahora evaluamos el choque con los proyectiles enemigos...
	if(proyectiles_enemigos.size())
	{
		for(auto& p : proyectiles_enemigos)
		{
			if(p->en_colision_con(jugador))
			{
				jugador.recibir_impacto(p->acc_potencia());
				p->mut_borrar(true);
			}
		}
	}

	/*
	* Cosas con las que se pueden chocar que no son bonus.
	*/

	Logica_colisionable lc(jugador);
	sala_actual->procesar_colisionables(lc);
}

/**
* @param Pantalla& pantalla : La pantalla sobre la que se dibuja.
*/

void Controlador_juego::dibujar(DLibV::Pantalla& pantalla)
{
	using namespace App_Interfaces;

	//Pantalla...
	pantalla.limpiar(128, 128, 128, 255);

	//Recolectar representables...
	std::vector<const Representable_I *> vr=(*sala_actual).obtener_vector_representables();
	vr.push_back(&jugador);

	for(const auto& p : proyectiles_jugador) vr.push_back(p.get());
	for(const auto& p : proyectiles_enemigos) vr.push_back(p.get());

	//TODO: Ordenar la vista.
	
	//Generar vista.
	representador.generar_vista(pantalla, vr);

	//Hud
	std::stringstream ss;
	ss<<jugador.acc_espaciable_x()<<","<<jugador.acc_espaciable_y()<<std::endl<<"HULL: "<<jugador.acc_salud()<<std::endl<<"ENERGY: "<<jugador.acc_energia()<<std::endl<<"SHIELD: "<<jugador.acc_escudo();

	DLibV::Representacion_texto_auto_estatica rep_hud(pantalla.acc_renderer(), DLibV::Gestor_superficies::obtener(App::Recursos_graficos::RS_FUENTE_BASE), ss.str());
	rep_hud.establecer_posicion(16, 16);
	rep_hud.volcar(pantalla);

	//Contador de tiempo...
	rep_hud.asignar(contador_tiempo.formatear_tiempo_restante());
	rep_hud.establecer_posicion(16, 52);
	rep_hud.volcar(pantalla);

	//Automapa	
	representador.dibujar_marco_automapa(pantalla);

	const auto& v=automapa.acc_vista();
	int x=0, y=0;

	for(const auto& u : v)
	{
		representador.dibujar_pieza_automapa(pantalla, x, y, u.visitado ? u.tipo : App_Definiciones::direcciones::nada);
		if(++x==App_Juego_Automapa::Definiciones_automapa::ANCHO)
		{
			x=0; ++y;
		}
	}
}

void Controlador_juego::refrescar_automapa()
{
	int x=sala_actual->acc_x(), y=sala_actual->acc_y();
	automapa.descubrir(x, y);
	automapa.refrescar_vista(x, y);
}

void Controlador_juego::iniciar_automapa()
{
	//Llegados a este punto podríamos usar de nuevo la información que
	//sacó el generador, mucho más legible, pero nos vamos a quedar con
	//esto, rápidamente...

	struct llamable_salas
	{
		struct info
		{
			int x, y;
			App_Definiciones::direcciones dir;
			info(int px, int py, App_Definiciones::direcciones pd)
				:x(px), y(py), dir(pd)
			{} 
		};

		std::vector<info> v;

		void operator()(const Sala& s)
		{
			v.push_back(info(s.acc_x(), s.acc_y(), s.acc_direcciones_entradas()) );
		}
	}ls;

	automapa.inicializar(mapa.acc_w(), mapa.acc_h());
	mapa.para_cada_sala(ls);
	for(const auto& i : ls.v) automapa.configurar(i.x, i.y, i.dir);


	refrescar_automapa();
}

void Controlador_juego::logica_proyectiles(float delta)
{
	auto procesar=[](Vsptr_Proyectil_base& proy, float delta, const Sala& sala)
	{
		for(auto& p : proy) 
		{
			//Comprobar la salida de la sala.
			Calculador_colisiones CC;
			auto cc=p->copia_caja();

			if(CC.es_fuera_de_sala(cc, sala)) p->mut_borrar(true);
			else
			{
				std::vector<const Celda *> celdas=CC.celdas_en_caja(cc, sala);
				if(celdas.size()) p->mut_borrar(true);
			}
		}

		auto it=std::remove_if(std::begin(proy), std::end(proy), [](sptr_Proyectil_base p) {return p->es_borrar();});
		if(it!=std::end(proy)) proy.erase(it, std::end(proy));

	};

	/**
	* Proyectiles del jugador y enemigos, proceso normal con borrado si procede.
	*/
	
	if(proyectiles_jugador.size()) procesar(proyectiles_jugador, delta, *sala_actual);
	if(proyectiles_enemigos.size()) procesar(proyectiles_enemigos, delta, *sala_actual);
}

void Controlador_juego::logica_mundo(float delta)
{
	/**
	* Cosas a las que les podemos disparar: controlar si cualquier proyectil
	* del jugador ha hecho impacto con ellas.
	*/

	if(proyectiles_jugador.size()) 
	{
		Logica_disparable ld(proyectiles_jugador);
		sala_actual->procesar_disparables(ld);
	}

	/**
	* Cosas que pueden añadir disparos al mundo... Básicamente controlar si
	* ha llegado el momento de disparar y hacer lo que sea. 
	* Aquí tenemos una mezcla interesante entre un visitante de Disparador y 
	* la clase lógica proyectiles, que controla la inserción de los mismos. 
	* Podemos convertir la lógica proyectiles en "procesador" para por hacer 
	* "procesar" de todos los objetos juego y, posteriormente, separar los 
	* "disparadores" y llamar a los visitantes propios.
	*/

	Logica_disparador lp(proyectiles_enemigos, jugador);
	sala_actual->procesar_disparadores(lp);

	/** 
	* Objeto para procesar la lógica de los turnos... Bien podría ser
	* una clase aparte si es necesario. Por un lado se procesan los objetos
	* de la sala y por otro los que quedan fuera.
	*/

	Logica_con_turno lct(jugador, *sala_actual, delta);
	sala_actual->procesar_con_turno(lct);

	std::vector<std::shared_ptr<App_Interfaces::Con_turno_I>> vpr;
	for(auto &p : proyectiles_jugador) vpr.push_back(p);
	for(auto &p : proyectiles_enemigos) vpr.push_back(p);
	lct.procesar(vpr);


	/**
	* Limpiar cualquier cosa que pueda haber desaparecido...
	*/

	sala_actual->limpiar_objetos_juego_para_borrar();
}
