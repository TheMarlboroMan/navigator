#include <algorithm>
#include <iterator>

#include "controlador_juego.h"
#include "../app/recursos.h"
#include "../app/definiciones/definiciones.h"

#include "../app/juego/logica/logica_disparador.h"
#include "../app/juego/logica/logica_con_turno.h"
#include "../app/juego/logica/logica_disparable.h"
#include "../app/juego/logica/logica_generador_objetos_juego.h"
#include "../app/juego/logica/contexto_turno_juego.h"
#include "../app/juego/logica/logica_efectos_colision.h"

using namespace App_Niveles;
using namespace App_Juego;
using namespace App_Juego_Logica;

Controlador_juego::Controlador_juego(Director_estados &DI, App_Niveles::Mapa& mapa, App_Juego_Automapa::Automapa& am, const App_Graficos::Animaciones& animaciones, const App_Lectores::Info_obstaculos_genericos& iog)
	:Controlador_base(DI),
	camara(0, 0, App_Definiciones::definiciones::w_vista, App_Definiciones::definiciones::h_vista),
	representador(animaciones),
	mapa(mapa),
	jugador(32.0, 32.0),
	automapa(am),
	vista_automapa(5, 5),
	info_obstaculos_genericos(iog),
	contador_tiempo(),
	sala_actual(nullptr),
	cambiar_modo_pantalla(false)
{
	sala_actual=&(mapa.obtener_sala_inicio());
	ajustar_camara_a_sala(*sala_actual);
	
	refrescar_automapa();

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
		if(input.es_input_down(Input::I_INTERCAMBIAR_PANTALLA_PAUSA))
		{
			solicitar_cambio_estado(Director_estados::t_estados::pausa);
			return;
		}

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
		sonar(delta);
		limpiar_eliminados();
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
	contenedor_volatiles.vaciar();
}

/**
* @param Jugador& : El objeto del tipo Jugador sobre el que se actúa.
* @param float : El tiempo delta.
*/

void Controlador_juego::procesar_jugador(Jugador& j, float delta, App_Input::Input_usuario iu)
{
	using namespace App_Colisiones;

	//TODO... No me gusta nada de nada. Deberíamos meterlo en el turno, quizás...
	if(iu.usar == App_Input::Input_usuario::t_estados::down)
	{
		if(jugador.disparar())
		{
			Logica_disparador lp(jugador);
			lp.insertar_disparo_jugador(contenedor_volatiles.proyectiles_jugador);
		}
	}

	j.recoger_input(iu);
	j.turno(delta);

	auto v=j.acc_vector();
	if(v.y) 
	{
		jugador.desplazar_caja(0.0, v.y * delta);
		Calculador_colisiones CC;
		auto v=CC.solidos_en_caja_sala(jugador.copia_caja(), *sala_actual);
		if(v.size()) CC.ajustar_colisiones_eje_y_actor_movil_con_espaciables(jugador, v);
	}

	if(v.x) 
	{
		jugador.desplazar_caja(v.x * delta, 0.0);
		Calculador_colisiones CC;
		auto v=CC.solidos_en_caja_sala(jugador.copia_caja(), *sala_actual);
		if(v.size()) CC.ajustar_colisiones_eje_x_actor_movil_con_espaciables(jugador, v);
	}

	//Las colisiones con objetos de juego se evaluan en la posición final.
	
	auto vec=sala_actual->acc_objetos_juego().recolectar_efectos_colision();
	Logica_efectos_colision lec(contador_tiempo, jugador);
	lec.procesar(vec);
	if(lec.es_salida_nivel())
	{
		abandonar_aplicacion();
	}

	//Ahora evaluamos el choque con los proyectiles enemigos...
	if(contenedor_volatiles.proyectiles_enemigos.size())
	{
		for(auto& p : contenedor_volatiles.proyectiles_enemigos)
		{
			if(!p->es_borrar() && p->en_colision_con(jugador))
			{
				jugador.recibir_impacto(p->acc_potencia());
				p->colisionar_con_jugador();
			}
		}
	}

	/**
	* Comprobar si está "aterrizado...".
	*/

	auto c=jugador.copia_caja_desplazada(0.0, 1.0);
	Calculador_colisiones CC;
	jugador.contabilizar_tiempo_aterrizado(CC.celdas_en_caja(c, *sala_actual).size() ? delta : 0.0);
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

	for(const auto& p : contenedor_volatiles.proyectiles_jugador) vr.push_back(p.get());
	for(const auto& p : contenedor_volatiles.proyectiles_enemigos) vr.push_back(p.get());
	for(const auto& p : contenedor_volatiles.particulas) vr.push_back(p.get());

	//Eliminar los que se vayan a borrar...
	auto it=std::remove_if(std::begin(vr), std::end(vr), [](const Representable_I * r) {return r->es_representable_borrar();});
	vr.erase(it, std::end(vr));
	
	//Ordenarlos...
	App_Interfaces::Ordenador_representables ord;
	std::sort(std::begin(vr), std::end(vr), ord);

	//Generar vista.
	representador.generar_vista(pantalla, camara, vr);

	//Hud
	representador.generar_hud(pantalla, jugador.acc_salud(), jugador.acc_energia(), jugador.acc_escudo(), contador_tiempo.formatear_tiempo_restante());

	//Automapa
	representador.generar_vista(pantalla, vista_automapa.obtener_vista(400, 412, 7));
}

void Controlador_juego::refrescar_automapa()
{
	int x=sala_actual->acc_x(), y=sala_actual->acc_y();
	automapa.descubrir(x, y);
	automapa.establecer_posicion_jugador(x, y);
	vista_automapa.refrescar_vista(automapa, x, y);
}

void Controlador_juego::logica_proyectiles(float delta)
{
	using namespace App_Colisiones;

	auto procesar=[](App_Juego_Contenedores::Contenedor_volatiles::Vsptr_Proyectil_base& proy, float delta, const Sala& sala)
	{
		for(auto& p : proy) 
		{
			//Comprobar la salida de la sala.
			Calculador_colisiones CC;
			auto cc=p->copia_caja();

			if(CC.es_fuera_de_sala(cc, sala)) 
			{
				p->mut_borrar(true);
			}
			else
			{
				//En caso de proyectiles móviles, implicaría borrar...
				if(CC.solidos_en_caja_sala(cc, sala).size()) p->colisionar_con_nivel(); 
			}
		}
	};

	/**
	* Proyectiles del jugador y enemigos...
	*/
	
	if(contenedor_volatiles.proyectiles_jugador.size()) procesar(contenedor_volatiles.proyectiles_jugador, delta, *sala_actual);
	if(contenedor_volatiles.proyectiles_enemigos.size()) procesar(contenedor_volatiles.proyectiles_enemigos, delta, *sala_actual);
}

void Controlador_juego::logica_mundo(float delta)
{
	/**
	* Cosas a las que les podemos disparar: controlar si cualquier proyectil
	* del jugador ha hecho impacto con ellas.
	*/

	if(contenedor_volatiles.proyectiles_jugador.size()) 
	{
		Logica_disparable ld(contenedor_volatiles.proyectiles_jugador);
		auto vd=sala_actual->acc_objetos_juego().recolectar_disparables();
		ld.procesar(vd);
	}

	/** 
	* Objeto para procesar la lógica de los turnos...
	*/

	using namespace App_Interfaces;
	std::vector<Con_turno_I *> vct=sala_actual->acc_objetos_juego().recolectar_con_turno();

	for(auto& p : contenedor_volatiles.particulas) 			vct.push_back(p.get());
	for(auto &p : contenedor_volatiles.proyectiles_jugador) 	vct.push_back(p.get());
	for(auto &p : contenedor_volatiles.proyectiles_enemigos) 	vct.push_back(p.get());
	for(auto &p : contenedor_volatiles.trazadores) 			vct.push_back(p.get());

	Contexto_turno_juego ctj(delta, *sala_actual, jugador);
	Logica_con_turno lct(ctj);
	lct.procesar(vct);

	/*****
	* Los que pueden crear nuevos objetos...
	*/

	auto vgoj=sala_actual->acc_objetos_juego().recolectar_generadores_objetos_juego();
	for(auto &p : contenedor_volatiles.proyectiles_jugador) vgoj.push_back(p.get());
	for(auto &p : contenedor_volatiles.proyectiles_enemigos) vgoj.push_back(p.get());
	for(auto &p : contenedor_volatiles.trazadores) vgoj.push_back(p.get());

	Logica_generador_objetos_juego lgoj(jugador, info_obstaculos_genericos);
	lgoj.procesar(vgoj);
	if(lgoj.hay_nuevos()) sala_actual->fusionar_objetos_juego(lgoj.acc_contenedor());
	if(lgoj.hay_volatiles()) contenedor_volatiles.fusionar_con(lgoj.acc_contenedor_volatiles());
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

void Controlador_juego::sonar(float delta)
{
	auto vs=(*sala_actual).obtener_vector_sonoros();
	for(auto& p : contenedor_volatiles.proyectiles_jugador) vs.push_back(p.get());
	for(auto& p : contenedor_volatiles.proyectiles_enemigos) vs.push_back(p.get());
	vs.push_back(&jugador);

	for(auto& s : vs)
	{
		if(s->hay_reproducir())
		{
			auto &v=s->acc_reproducir();
			for(auto& r : v) gestor_audio.insertar(r);
			s->reset_reproducir();
		}

		if(s->hay_detener())
		{
			auto &v=s->acc_detener();
			for(auto& r : v) gestor_audio.insertar(r);
			s->reset_detener();
		}
	}	

	gestor_audio.turno(delta);
}

void Controlador_juego::limpiar_eliminados()
{
	sala_actual->limpiar_objetos_juego_para_borrar();
	contenedor_volatiles.limpiar_para_borrar();
}
