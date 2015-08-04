#include <algorithm>

#include "controlador_juego.h"
#include "../app/recursos.h"
#include "../app/definiciones/definiciones.h"
#include "../app/generador/traductor_mapas.h"
#include "../app/generador/generador_estructura_niveles.h"

#include "../app/visitantes/visitante_objeto_juego.h"
#include "../app/juego/logica_bonus.h"
#include "../app/juego/logica_proyectiles.h"
#include "../app/juego/objetos_juego/bonus_tiempo.h"
#include "../app/juego/objetos_juego/bonus_escudo.h"

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

		if(iu.usar)
		{
			Logica_proyectiles lp;
			lp.insertar_disparo_jugador(proyectiles_jugador, jugador);
		}

		procesar_jugador(jugador, delta, iu);

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
	
		controlar_salida_sala(jugador);

		logica_proyectiles(delta);
		logica_mundo(delta);
	}
}

/**
* @param Jugador j
*
* TODO: Ajustar coordenadas para que sea menos instantáneo.
* Controla que el jugador ha salido de una sala.
*/

void Controlador_juego::controlar_salida_sala(Jugador& j)
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
		
		try
		{
			//TODO: Mover a otro método todo el tema de cargar una nueva sala.
			proyectiles_jugador.clear();
			sala_actual=&mapa.obtener_sala(ax, ay);
			const auto& s=sala_actual->obtener_entrada_posicion(obtener_direccion_contraria(salida));
			j.establecer_en_posicion(s);
			refrescar_automapa();
		}
		catch(std::logic_error& e)
		{
			LOG<<"ERROR AL CAMBIAR DE SALA: "<<e.what()<<std::endl;
			abandonar_aplicacion();
		}
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

	//Las colisiones con objetos de juego se evaluan en la posición final.

	//En primer lugar evaluamos los items.

	using namespace App_Visitantes;
	Logica_bonus lb(contador_tiempo);

	class Visitante_bonus:public Visitante_objeto_juego
	{
		///////////
		//Interface pública.
		public:
		Visitante_bonus(
			App_Interfaces::Logica_bonus_I& b, 
			App_Interfaces::Espaciable& e)
			:lb(b), es(e)
		{}

		virtual void 			visitar(App_Juego_ObjetoJuego::Bonus_tiempo& b) {if(b.en_colision_con(es)) lb.recoger_bonus_tiempo(b);}
		virtual void 			visitar(App_Juego_ObjetoJuego::Bonus_escudo& b) {/*if(b.en_colision_con(e)) lb.recoger_bonus_escudo(b);*/}

		////////////
		//Propiedades.
		private:
		App_Interfaces::Logica_bonus_I& lb;
		App_Interfaces::Espaciable& 	es;
	}vis(lb, jugador);

	sala_actual->procesar_visitante_objetos_juego(vis);

	//TODO: ¿Cómo evaluar cosas que detengan el movimiento?.	
}

/**
* @param Pantalla& pantalla : La pantalla sobre la que se dibuja.
*/

void Controlador_juego::dibujar(DLibV::Pantalla& pantalla)
{
	//Pantalla...
	pantalla.limpiar(128, 128, 128, 255);

	//Recolectar representables...
	std::vector<const Representable *> vr=(*sala_actual).obtener_vector_representables();
	vr.push_back(&jugador);
	for(const auto& p : proyectiles_jugador) vr.push_back(p.get());

	//TODO: Ordenar.
	
	//Generar vista.
	representador.generar_vista(pantalla, vr);

	//Hud
	std::stringstream ss;
	ss<<jugador.acc_espaciable_x()<<","<<jugador.acc_espaciable_y()<<std::endl<<" HULL: "<<jugador.acc_salud()<<" SHIELD: "<<jugador.acc_escudo();

	DLibV::Representacion_texto_auto_estatica rep_hud(pantalla.acc_renderer(), DLibV::Gestor_superficies::obtener(App::Recursos_graficos::RS_FUENTE_BASE), ss.str());
	rep_hud.establecer_posicion(16, 16);
	rep_hud.volcar(pantalla);

	//Contador de tiempo...
	rep_hud.asignar(contador_tiempo.formatear_tiempo_restante());
	rep_hud.establecer_posicion(16, 32);
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
	for(auto& p : proyectiles_jugador) 
	{
		p->turno(delta);

		//Comprobar que choquen o no con algo.
		Calculador_colisiones CC;
		auto cc=p->copia_caja();

		if(CC.es_fuera_de_sala(cc, *sala_actual)) p->mut_borrar(true);
		else
		{
			std::vector<const Celda *> celdas=CC.celdas_en_caja(cc, *sala_actual);
			if(celdas.size()) p->mut_borrar(true);
		}
	}

	auto it=std::remove_if(std::begin(proyectiles_jugador), std::end(proyectiles_jugador), [](std::shared_ptr<App_Juego_Proyectiles::Proyectil_base> p) {return p->es_borrar();});
	if(it!=std::end(proyectiles_jugador)) proyectiles_jugador.erase(it, std::end(proyectiles_jugador));
}

void Controlador_juego::logica_mundo(float delta)
{
	sala_actual->limpiar_objetos_juego_para_borrar();
}
