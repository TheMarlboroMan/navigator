#include "jugador.h"

using namespace App_Juego;
using namespace App_Graficos;
using namespace App;

const float Jugador::ACELERACION_VERTICAL_SEGUNDO=200.0;
const float Jugador::ACELERACION_HORIZONTAL_SEGUNDO=300.0;
const float Jugador::DECELERACION_HORIZONTAL_SEGUNDO=350.0;
const float Jugador::MAXIMA_VELOCIDAD_HORIZONTAL=200.0;
const float Jugador::MAXIMA_VELOCIDAD_VERTICAL=150.0;
const float Jugador::MAXIMA_VELOCIDAD_CAIDA=150.0;
const float Jugador::VELOCIDAD_MINIMA_IMPACTO=100.0;
const float Jugador::COOLOFF_RECUPERAR_ESCUDO=0.8f;

Jugador::Jugador(float x, float y)
	:Actor_movil(x, y, W, H),
	posicion_anterior(copia_caja()),
	salud(MAX_SALUD), escudo(MAX_ESCUDO), cooloff_escudo(0.0f),
//	TREC("data/recortes/jugador.dat"),	
	direccion(App_Definiciones::direcciones::derecha)
{
	establecer_vector(100.0, Movil::t_vector::V_X);
}

Jugador::~Jugador()
{

}

void Jugador::callback_ajuste(float pos, Actor_movil::posiciones_ajuste tipo)
{
	switch(tipo)
	{
		case Actor_movil::posiciones_ajuste::arriba:
		case Actor_movil::posiciones_ajuste::abajo:
		{
			//TODO: Función para recibir impacto.		
			float fv=abs(acc_vector_y());
			float nv=0.0;

			if(fv >= VELOCIDAD_MINIMA_IMPACTO) 
			{
				recibir_impacto(fv);
				nv=-acc_vector_y() / 2.0;
			}

			establecer_vector(nv, Movil::t_vector::V_Y);
		}	
		break;
		case Actor_movil::posiciones_ajuste::izquierda:
		case Actor_movil::posiciones_ajuste::derecha:
		{
			float fv=abs(acc_vector_x());
			float nv=0.0;
			if(fv >= VELOCIDAD_MINIMA_IMPACTO) 
			{
				recibir_impacto(fv);
				nv=-acc_vector_x() / 2.0;
			}
			establecer_vector(nv, Movil::t_vector::V_X);
		}
		break;
		case Actor_movil::posiciones_ajuste::nada:
			//Noop.
		break;
	}
}

/**
* @param float val : valor del impacto recibido, el vector de colisión, por ejemplo.
*/

void Jugador::recibir_impacto(float val)
{
	if(val < escudo)
	{
		escudo-=val;
		salud-=val / 4;
	}
	else
	{
		float dif=val-escudo;
		escudo=0.0;
		salud-=dif;
	}

	if(escudo < 0.0) escudo=0.0;
	if(salud < 0.0) salud=0.0;
	cooloff_escudo=COOLOFF_RECUPERAR_ESCUDO;

}

void Jugador::transformar_bloque(Bloque_transformacion_representable &b) const
{
	//Se asume que todos los frames van mirando a la derecha.
	b.establecer_tipo(Bloque_transformacion_representable::tipos::TR_BITMAP);
	b.establecer_alpha(255);
	b.establecer_recurso(Recursos_graficos::RT_DEFECTO);
	b.establecer_recorte(32, 0, 27, 16);
	b.establecer_posicion(acc_espaciable_x()-1, acc_espaciable_y()-1, 27, 16);
	b.invertir_horizontal(direccion==App_Definiciones::direcciones::izquierda);
}

void Jugador::turno(float delta)
{
//	salud=100.0f;
	posicion_anterior=copia_caja();
	cooloff_escudo-=delta;
	if(cooloff_escudo < 0.0f) cooloff_escudo=0.0;

	//Recuperación del escudo.
	if(escudo < MAX_ESCUDO && !cooloff_escudo)
	{
		escudo+=(delta * ESCUDO_RECUPERADO_POR_SEGUNDO);
		if(escudo > MAX_ESCUDO) escudo=MAX_ESCUDO;
	}

	//Frenada o aceleración.
	if(input.mov_horizontal)
	{
		float v=acc_vector_x();
		v+=(delta * ACELERACION_HORIZONTAL_SEGUNDO) * input.mov_horizontal;

		if(v > MAXIMA_VELOCIDAD_HORIZONTAL) v=MAXIMA_VELOCIDAD_HORIZONTAL;
		else if(v < -MAXIMA_VELOCIDAD_HORIZONTAL) v=-MAXIMA_VELOCIDAD_HORIZONTAL;

		establecer_vector(v, Movil::t_vector::V_X);

		if(input.mov_horizontal < 0) direccion=App_Definiciones::direcciones::izquierda;
		else direccion=App_Definiciones::direcciones::derecha;

	}
	else
	{
		float v=abs(acc_vector_x());
		v-=(delta * ACELERACION_HORIZONTAL_SEGUNDO);
		if(v < 0.0) v=0;

		//Aproximarse al cero.
		float vr=acc_vector_x();
		if(vr > 0.0) establecer_vector(v, Movil::t_vector::V_X);
		else if(vr < 0.0) establecer_vector(-v, Movil::t_vector::V_X);	
	}

	if(input.mov_vertical)
	{
		float v=acc_vector_y();
		v+=(delta * ACELERACION_VERTICAL_SEGUNDO) * input.mov_vertical;

		if(v > 0.0 && v > MAXIMA_VELOCIDAD_VERTICAL) v=MAXIMA_VELOCIDAD_VERTICAL;
		else if(v < 0.0 && v < -MAXIMA_VELOCIDAD_CAIDA) v=-MAXIMA_VELOCIDAD_CAIDA;

		establecer_vector(v, Movil::t_vector::V_Y);
	}
}

/**
* @param float v : Cantidad de salud a sumar.
*/

void Jugador::sumar_salud(float v)
{
	salud+=v;
	if(salud > MAX_SALUD) salud=MAX_SALUD;
}
