#include "disparador_estatico.h"

using namespace App_Juego_ObjetoJuego;

Disparador_estatico::Disparador_estatico(float x, float y, float t, float p, float d, App_Definiciones::direcciones dir, int longitud)
	:Objeto_juego_I(),
	Actor(x, y, App_Definiciones::definiciones::dim_celda, App_Definiciones::definiciones::dim_celda),
	direccion(dir), tiempo_base(t), tiempo_actual(0.0f),
	pausa_inicial(p), duracion_disparo(d),
	longitud(longitud)
{

}

void Disparador_estatico::turno(App_Interfaces::Contexto_turno_I& ct)
{
	float delta=ct.acc_delta();

	if(pausa_inicial)
	{
		pausa_inicial-=delta;
		if(pausa_inicial <= 0.0f) pausa_inicial=0.0f;
	}
	else
	{
		tiempo_actual-=delta;
	}
}

void Disparador_estatico::generar_objetos(App_Interfaces::Factoria_objetos_juego_I& foj)
{
	if(!pausa_inicial && tiempo_actual <= 0.0f)
	{
		tiempo_actual=tiempo_base;

		int w=8, h=8;
		float x=acc_espaciable_cx()-(w/2), y=acc_espaciable_cy()-(h/2);

		//Colocar el punto de salida del disparo donde corresponda....
		switch(direccion)
		{
			case App_Definiciones::direcciones::arriba: 
				h=App_Definiciones::definiciones::dim_celda * longitud;
				y=acc_espaciable_y()-h;
			break;
			case App_Definiciones::direcciones::abajo: 
				y=acc_espaciable_fy();
				h=App_Definiciones::definiciones::dim_celda * longitud;
			break;
			case App_Definiciones::direcciones::derecha: 
				x=acc_espaciable_fx();
				w=App_Definiciones::definiciones::dim_celda * longitud;
			break;
			case App_Definiciones::direcciones::izquierda: 
				w=App_Definiciones::definiciones::dim_celda * longitud;
				x=acc_espaciable_x()-w;
			break;
			default: break;
		}

		foj.fabricar_proyectil_rayo_estatico_enemigo(x, y, w, h, duracion_disparo);

		//TODO: Los concerns de audio están mezlados con el resto :(.
		insertar_reproducir(App_Audio::Info_audio_reproducir(
			App_Audio::Info_audio_reproducir::t_reproduccion::simple,
			App_Audio::Info_audio_reproducir::t_sonido::repetible,  
			App::Recursos_audio::rs_disparo_rayo, 127, 127));
	}
}
