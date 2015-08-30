#include "enemigo_basico.h"

using namespace App_Juego_ObjetoJuego;

const float Enemigo_basico::SALUD_DEFECTO=30.0f;
const float Enemigo_basico::TIEMPO_PROXIMO_DISPARO_DEFECTO=3.0f;

Enemigo_basico::Enemigo_basico(float px, float py, float s)
	:
	Objeto_juego_I(),
	Actor_movil(px, py, W, H),
	salud(s),
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


void Enemigo_basico::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
{
	using namespace App_Graficos;

	//Se asume que todos los frames van mirando a la derecha.
	b.establecer_tipo(Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(255);
	b.establecer_recurso(App::Recursos_graficos::rt_defecto);
	b.establecer_recorte(32, 0, 27, 16);
	b.establecer_posicion(acc_espaciable_x()-1, acc_espaciable_y()-1, W, H);
	b.invertir_horizontal(direccion==App_Definiciones::direcciones::izquierda);
}

void Enemigo_basico::turno(App_Interfaces::Contexto_turno_I& ct)
{
	float delta=ct.acc_delta();
	tiempo_proximo_disparo-=delta;
}

void Enemigo_basico::recibir_disparo(float potencia)
{
	int id_sonido=App::Recursos_audio::rs_explosion;

	salud-=potencia;
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
		auto g=HerramientasProyecto::Generador_int(10, 30);
		auto gvel=HerramientasProyecto::Generador_int(150, 300);
		int i=0, mp=g();
		while(i < mp)
		{
			auto g=HerramientasProyecto::Generador_int(0, 359);
			auto v=Vector_2d::vector_unidad_para_angulo(g())*gvel();
			f.fabricar_chatarra(x, y, 3.0f, v);
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

			const auto v=obtener_vector_para(f.acc_blanco_disparo()) * 200.0f;
			f.fabricar_proyectil_normal_enemigo(acc_espaciable_x(), acc_espaciable_y(), 8, 8, v, 25.0);

			//TODO: Los concerns de audio están mezlados con el resto :(.
			insertar_reproducir(App_Audio::Info_audio_reproducir(
				App_Audio::Info_audio_reproducir::t_reproduccion::simple,
				App_Audio::Info_audio_reproducir::t_sonido::repetible,  
				App::Recursos_audio::rs_disparo, 127, 127));
		}
	}
}
