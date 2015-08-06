#include "enemigo_basico.h"

using namespace App_Juego_ObjetoJuego;

const float Enemigo_basico::SALUD_DEFECTO=30.0f;
const float Enemigo_basico::TIEMPO_PROXIMO_DISPARO_DEFECTO=3.0f;

Enemigo_basico::Enemigo_basico(float px, float py, float s)
	:Actor(px, py, W, H),
	Borrable_I(),
	salud(s),
	tiempo_proximo_disparo(TIEMPO_PROXIMO_DISPARO_DEFECTO),
	direccion(App_Definiciones::direcciones::derecha)
{

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
		tiempo_proximo_disparo=TIEMPO_PROXIMO_DISPARO_DEFECTO;
		direccion=direccion==App_Definiciones::direcciones::izquierda ? App_Definiciones::direcciones::derecha : App_Definiciones::direcciones::izquierda;
	}
}
