#include "proyectil_base.h"

using namespace App_Juego_Proyectiles;

Proyectil_base::Proyectil_base(float x, float y, unsigned int w, unsigned int h):
	Actor_movil(x, y, w, h),
	Borrable_I(),
	potencia(0.0f)
{

}

void Proyectil_base::establecer_vector(const DLibH::Vector_2d& v)
{
	Movil::establecer_vector(v);
}
