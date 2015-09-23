#include "enemigo_basico.h"

using namespace App_Juego_ObjetoJuego;

const float Enemigo_basico::SALUD_DEFECTO=30.0f;
const float Enemigo_basico::TIEMPO_PROXIMO_DISPARO_DEFECTO=3.0f;

Enemigo_basico::Enemigo_basico(float px, float py, float s)
	:
	Objeto_juego_I(),
	Actor_movil(px, py, W, H),
	salud(s), salud_max(s),
	tiempo_proximo_disparo(TIEMPO_PROXIMO_DISPARO_DEFECTO),
	direccion(App_Definiciones::direcciones::derecha)
{
	//TODO: esto no me gusta aquí.
	establecer_vector(DLibH::Vector_2d(0.0f, 60.0));
}

unsigned short int Enemigo_basico::obtener_profundidad_ordenacion()const
{
	return 10;
}

unsigned int Enemigo_basico::obtener_ciclos_representable()const
{
	return 1;
}

void Enemigo_basico::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
{
	using namespace App_Graficos;
	using namespace App_Definiciones;
	const auto& f=b.obtener_frame(animaciones::sprites, animaciones_sprites::enemigo_basico, 0);

	//Se asume que todos los frames van mirando a la derecha.
	b.establecer_tipo(Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(255);
	b.establecer_recurso(App::Recursos_graficos::rt_juego);
	b.establecer_recorte(f.x, f.y, f.w, f.h);
	b.establecer_posicion(acc_espaciable_x()+f.desp_x, acc_espaciable_y()+f.desp_y, W, H);
	b.invertir_horizontal(direccion==App_Definiciones::direcciones::izquierda);
}

void Enemigo_basico::turno(App_Interfaces::Contexto_turno_I& ct)
{
	float delta=ct.acc_delta();
	tiempo_proximo_disparo-=delta;

	//Encarar al jugador.
	auto vd=obtener_vector_pantalla_para(ct.acc_blanco());

	mut_direccion(vd.x < 0.0 ? App_Definiciones::direcciones::izquierda : App_Definiciones::direcciones::derecha);

	//Moverse...
	auto v=acc_vector();
	desplazar_caja(v.x * delta, v.y * delta);

	//En caso de colisión o salir fuera del mundo, revertir.
	auto caja=copia_caja();
	if(ct.es_fuera_sala(caja) || ct.celdas_en_caja(caja).size())
	{
		v.x=-v.x;
		v.y=-v.y;
		establecer_vector(v);
	}
}

void Enemigo_basico::recibir_disparo(float potencia, App_Interfaces::Disparable_contexto_I& contexto)
{
	int id_sonido=App::Recursos_audio::rs_explosion;

	salud-=potencia;

	contexto.insertar_marcador(potencia, acc_espaciable_cx(), acc_espaciable_y());	
	contexto.asignar_barra(salud_max, salud, "SENTRY");

	if(salud <= 0.0) 
	{
		mut_borrar(true);
	}
	else
	{
		id_sonido=App::Recursos_audio::rs_golpe;
	}

	insertar_reproducir(App_Audio::Info_audio_reproducir(
		App_Audio::Info_audio_reproducir::t_reproduccion::simple,
		App_Audio::Info_audio_reproducir::t_sonido::repetible,  
		id_sonido, 127, 127));
}

void Enemigo_basico::generar_objetos(App_Interfaces::Factoria_objetos_juego_I& f)
{
	if(es_borrar())
	{
		const auto& v=acc_vector();

		float x=acc_espaciable_x()+(acc_espaciable_w()/2);
		float y=acc_espaciable_y()+(acc_espaciable_w()/2);
		auto g=Herramientas_proyecto::Generador_int(10, 30);
		auto gvel=Herramientas_proyecto::Generador_int(150, 300);
		int i=0, mp=g();
		while(i < mp)
		{
			auto g=Herramientas_proyecto::Generador_int(0, 359);
			auto v=Vector_2d::vector_unidad_para_angulo(g())*gvel();
			f.fabricar_chatarra(x, y, 3.0f, v);
			++i;
		}

		auto gtraza=Herramientas_proyecto::Generador_int(3, 5);
		auto gveltraza=Herramientas_proyecto::Generador_int(160, 200);
		auto gduracion=Herramientas_proyecto::Generador_int(40, 100);
		i=0;
		while(i < gtraza())
		{
			auto g=Herramientas_proyecto::Generador_int(0, 359);
			auto v=Vector_2d::vector_unidad_para_angulo(g())*gveltraza();
			float dur=(float)gduracion() / 100.0;
			f.fabricar_trazador_humo(x, y, dur, v);
			++i;
		}

		f.fabricar_bonus_tiempo(acc_espaciable_x(), acc_espaciable_y(), 5.0f);
		f.fabricar_explosion(x, y, 1.0f, v);
	}
	else
	{
		if(tiempo_proximo_disparo < 0.0f) 
		{
			tiempo_proximo_disparo=TIEMPO_PROXIMO_DISPARO_DEFECTO;

			const auto v=obtener_vector_pantalla_para(f.acc_blanco_disparo()) * 200.0f;
			f.fabricar_proyectil_normal_enemigo(acc_espaciable_x(), acc_espaciable_y(), 8, 8, v, 25.0);

			//TODO: Los concerns de audio están mezlados con el resto :(.
			insertar_reproducir(App_Audio::Info_audio_reproducir(
				App_Audio::Info_audio_reproducir::t_reproduccion::simple,
				App_Audio::Info_audio_reproducir::t_sonido::repetible,  
				App::Recursos_audio::rs_disparo, 127, 127));
		}
	}
}

void Enemigo_basico::efecto_colision(App_Interfaces::Efecto_colision_recogedor_I& er)
{
	er.recibir_impacto(2.5f);
}
