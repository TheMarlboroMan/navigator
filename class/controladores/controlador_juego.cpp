#include <algorithm>

#include "controlador_juego.h"
#include "../app/recursos.h"
#include "../app/definiciones/definiciones.h"

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

Controlador_juego::Controlador_juego(Director_estados &DI, App_Niveles::Mapa& p_mapa)
	:Controlador_base(DI),
	camara(0, 0, App_Definiciones::definiciones::w_vista, App_Definiciones::definiciones::h_vista),
	mapa(p_mapa),
	jugador(32.0, 32.0),
	contador_tiempo(),
	sala_actual(nullptr),
	cambiar_modo_pantalla(false)
{
	sala_actual=&(mapa.obtener_sala_inicio());
	ajustar_camara_a_sala(*sala_actual);

	iniciar_automapa();

	const auto& pi=sala_actual->obtener_posicion_inicial_jugador();
	if(!pi)
	{
		LOG<<"ERROR: No se localiza posición inicial para jugador al iniciar nivel.";
		abandonar_aplicacion();
	}
	else
	{
		jugador.establecer_posicion(pi->acc_espaciable_x(), pi->acc_espaciable_y());
	}

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
	using namespace App_Input;

	if(input.es_senal_salida() || input.es_input_down(Input::I_ESCAPE))
	{
		abandonar_aplicacion();
	}
	else
	{
	/**
	* Almacenamos la orden para poder enviarla allá donde haya 
	* información de pantalla.
	* TODO: Sacarlo de dibujar y llevarlo al bootstrap.
	*/
	if(!cambiar_modo_pantalla) 
	{
		cambiar_modo_pantalla=input.es_input_down(Input::I_CAMBIAR_MODO_PANTALLA);
	}

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
*/

bool Controlador_juego::controlar_y_efectuar_salida_sala(Jugador& j)
{
	using namespace App_Definiciones;

	direcciones salida=direcciones::nada;

	if(j.acc_espaciable_x() < 0) salida=direcciones::izquierda;
	else if(j.acc_espaciable_fx() >= sala_actual->acc_w()*definiciones::dim_celda) salida=direcciones::derecha;
	else if(j.acc_espaciable_y() < 0) salida=direcciones::arriba;
	else if(j.acc_espaciable_fy() > sala_actual->acc_h()*definiciones::dim_celda) salida=direcciones::abajo;

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

		//Calcular el offset con respecto a la salida para luego aplicarlo
		//de nuevo en la entrada. Asume que todas las entradas y salidas
		//tienen la misma dimensión, rollo Metroid :D.
		auto& s=sala_actual->obtener_entrada_posicion(salida);
		DLibH::Punto_2d<int> offset(s.acc_espaciable_x()-j.acc_espaciable_x(), s.acc_espaciable_y()-j.acc_espaciable_y());

		cargar_sala(ax, ay, salida, j, offset);
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

void Controlador_juego::cargar_sala(int ax, int ay, App_Definiciones::direcciones salida, Jugador& j, DLibH::Punto_2d<int> offset)
{
	try
	{
		limpiar_pre_cambio_sala();

		sala_actual=&mapa.obtener_sala(ax, ay);
		const auto& entrada=sala_actual->obtener_entrada_posicion(obtener_direccion_contraria(salida));

		//Colocar al jugador en la entrada y aplicar el offset.
		using namespace App_Definiciones;
		j.establecer_posicion(entrada);
		switch(salida)
		{
			case direcciones::izquierda:
			case direcciones::derecha:
				j.desplazar_caja(0.0f, -offset.y);
			break;
			case direcciones::arriba:
			case direcciones::abajo:
				j.desplazar_caja(-offset.x, 0.0f);
			break;
			case direcciones::nada: break;
		}
			
		refrescar_automapa();
		ajustar_camara_a_sala(*sala_actual);
		

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
	proyectiles_enemigos.clear();
}

/**
* @param Jugador& : El objeto del tipo Jugador sobre el que se actúa.
* @param float : El tiempo delta.
*/

void Controlador_juego::procesar_jugador(Jugador& j, float delta, App_Input::Input_usuario iu)
{
	using namespace App_Colisiones;

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

	/**
	* Comprobar si está "aterrizado...".
	*/

	auto c=jugador.copia_caja_desplazada(0.0, 1.0);
	Calculador_colisiones CC;
	jugador.contabilizar_tiempo_aterrizado(CC.celdas_en_caja(c, *sala_actual).size() ? delta : 0.0);

	/*
	* Cosas con las que se pueden chocar que no son bonus. El objeto de 
	* salida puede provocar el fin del nivel si el jugador aterriza al lado.
	*/

	Logica_colisionable lc(jugador);
	sala_actual->procesar_colisionables(lc);
	if(lc.es_salida_nivel())
	{
		//TODO...
		abandonar_aplicacion();
	}
}

/**
* @param Pantalla& pantalla : La pantalla sobre la que se dibuja.
*/

void Controlador_juego::dibujar(DLibV::Pantalla& pantalla)
{
	//TODO: Quitar esto de aquí, no pertenece. Llevarlo al bootstrap.
	if(cambiar_modo_pantalla)
	{
		//TODO: El cambio jode. For real.
		auto mv=pantalla.acc_modo_ventana();
		++mv;
		if(mv >= DLibV::Pantalla::M_MAX_MODO) mv=0;
		pantalla.establecer_modo_ventana(mv);
		cambiar_modo_pantalla=false;
	}

	using namespace App_Graficos;
	using namespace App_Interfaces;

	//Pantalla...
	pantalla.limpiar(0, 0, 0, 255);
	evaluar_enfoque_camara();
//	auto c=camara.acc_caja_pos();
	
//SDL_Rect cp=DLibH::Herramientas_SDL::nuevo_sdl_rect(c.x, c.y, c.w, c.h);
//DLibV::Representacion_primitiva_caja_estatica CAJA(cp, 128, 128, 128);
//CAJA.volcar(pantalla);

	/**
	* TODO: Usar foco de la cámara para trimear lo que mostramos si la sala
	* es más grande que la cámara en un factor de... 1.2?.
	* const auto& c_foco=camara.acc_caja_foco();
	* const Espaciable::t_caja caja(c_foco.x, c_foco.y, c_foco.w, c_foco.h);
	*/


	//Recolectar representables...
	std::vector<const Representable_I *> vr=(*sala_actual).obtener_vector_representables();
	vr.push_back(&jugador);

	for(const auto& p : proyectiles_jugador) vr.push_back(p.get());
	for(const auto& p : proyectiles_enemigos) vr.push_back(p.get());

	//TODO: Ordenar la vista.
	
	//Generar vista.
	representador.generar_vista(pantalla, camara, vr);

	//Hud
	representador.generar_hud(pantalla, jugador.acc_salud(), jugador.acc_energia(), jugador.acc_escudo(), contador_tiempo.formatear_tiempo_restante());

	//Automapa	
	//representador.dibujar_marco_automapa(pantalla);

	const auto& v=automapa.acc_vista();
	int x=0, y=0;

	for(const auto& u : v)
	{
		bool es_actual=static_cast<int>(sala_actual->acc_x())==u.x && static_cast<int>(sala_actual->acc_y())==u.y;
		representador.dibujar_pieza_automapa(pantalla, x, y, u.visitado ? u.tipo : App_Definiciones::direcciones::nada, es_actual);
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
	using namespace App_Colisiones;

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


void Controlador_juego::evaluar_enfoque_camara()
{
	const auto& c_foco=camara.acc_caja_foco();
	int x=jugador.acc_espaciable_x()-(c_foco.w / 2 );
	int y=jugador.acc_espaciable_y()-(c_foco.h / 2);
	camara.enfocar_a(x, y);
}

/**
* Establece los límites de la cámara según la sala. Adicionalmente puede cambiar
* el tamaño y la posición de la cámara para salas más pequeñas que la misma.
*/ 

void Controlador_juego::ajustar_camara_a_sala(const Sala& s)
{
	using namespace App_Definiciones;
	const int w_sala=sala_actual->acc_w()*definiciones::dim_celda;
	const int h_sala=sala_actual->acc_h()*definiciones::dim_celda;

	camara.establecer_limites(0, 0, w_sala, h_sala);

	//TODO: Todo esto de la cámara es una mierda. Mejorar la librería.
	int w_pos=definiciones::w_vista, h_pos=definiciones::h_vista, x_pos=0, y_pos=0;
	if(w_sala < definiciones::w_vista || h_sala < definiciones::h_vista)
	{
		if(w_sala < definiciones::w_vista) 
		{
			w_pos=w_sala;
			x_pos=(definiciones::w_vista - w_sala) / 2;
		}

		if(h_sala < definiciones::h_vista) 
		{
			h_pos=h_sala;
			y_pos=(definiciones::h_vista - h_sala) / 2;
		}
	}

	camara.mut_w_pos(w_pos);
	camara.mut_h_pos(h_pos);
	camara.mut_pos_x(x_pos);
	camara.mut_pos_y(y_pos);

	camara.restaurar_enfoque();
}
