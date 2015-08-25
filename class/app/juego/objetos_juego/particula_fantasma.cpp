#include "particula_fantasma.h"

using namespace App_Juego_ObjetoJuego;

Particula_fantasma::Particula_fantasma(float x, float y, float tv, float ve)
	:App_Interfaces::Objeto_juego_I(),
	Particula_base(tv),
	velocidad_expansion(ve)
{
	//TODO: Hacer algo con x e y...
}

unsigned short int Particula_fantasma::obtener_profundidad_ordenacion()const
{
	return 30;
}

void Particula_fantasma::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	//TODO...
}

void Particula_fantasma::turno(float)
{
	//TODO
}
