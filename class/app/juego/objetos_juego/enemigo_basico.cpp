#include "enemigo_basico.h"

using namespace App_Juego_ObjetoJuego;

const float Enemigo_basico::SALUD_DEFECTO=30.0f;
const float Enemigo_basico::TIEMPO_PROXIMO_DISPARO_DEFECTO=3.0f;

Enemigo_basico::Enemigo_basico(float px, float py, float s)
	:
	Objeto_juego_I(),
	Actor_movil(px, py, W, H),
	Disparador_I(),
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
	b.establecer_tipo(Bloque_transformacion_representable::tipos::TR_BITMAP);
	b.establecer_alpha(255);
	b.establecer_recurso(App::Recursos_graficos::RT_DEFECTO);
	b.establecer_recorte(32, 0, 27, 16);
	b.establecer_posicion(acc_espaciable_x()-1, acc_espaciable_y()-1, W, H);
	b.invertir_horizontal(direccion==App_Definiciones::direcciones::izquierda);
}

/**
*@param float delta : cantidad de tiempo que ha pasado desde el último turno.
*/ 

void Enemigo_basico::turno(float delta)
{
	tiempo_proximo_disparo-=delta;
	if(tiempo_proximo_disparo < 0.0f) 
	{
		Disparador_I::mut_disparar(true);
		tiempo_proximo_disparo=TIEMPO_PROXIMO_DISPARO_DEFECTO;
	}
}

void Enemigo_basico::recibir_disparo(float potencia)
{
	salud-=potencia;
	if(salud <= 0.0) 
	{
		insertar_reproducir(App_Audio::Audio_reproducir(
			App_Audio::Audio_reproducir::tipos_reproduccion::simple, 
			App::Recursos_audio::rs_explosion, 127, 127));

		mut_borrar(true);
	}
}
