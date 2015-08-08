#include "proyectil_base.h"

using namespace App_Juego_ObjetoJuego;

Proyectil_base::Proyectil_base(float x, float y, unsigned int w, unsigned int h):
	Actor_movil(x, y, w, h),
	Objeto_juego_I(),
	potencia(0.0f)
{

}

void Proyectil_base::mut_potencia(float v)
{
	potencia=v;
	if(!potencia_original) potencia_original=v;
}

void Proyectil_base::establecer_vector(const DLibH::Vector_2d& v)
{
	Movil::establecer_vector(v);
}
