#include "particula_explosion.h"

using namespace App_Juego_ObjetoJuego;


Particula_explosion::Particula_explosion(float x, float y, float tv, const DLibH::Vector_2d& v):
	App_Interfaces::Objeto_juego_I(),
	Particula_base(tv),
	App_Juego::Actor_movil(x, y, 1.0, 1.0)
{
	establecer_vector(v);
}

unsigned short int Particula_explosion::obtener_profundidad_ordenacion()const
{
	return 30;
}

void Particula_explosion::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	//TODO TODO TODO...
}

void Particula_explosion::turno(float delta)
{
	//TODO TODO TODO
}

float Particula_explosion::obtener_peso() const
{
	return 0.0;
}
float Particula_explosion::obtener_max_velocidad_caida() const
{
	return 0.0;
}

void Particula_explosion::callback_ajuste(float pos, posiciones_ajuste tipo)
{
	//Nada de nada...
}
