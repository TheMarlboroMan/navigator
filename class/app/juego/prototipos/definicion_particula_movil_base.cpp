#include "definicion_particula_movil_base.h"

using namespace App_Juego_Prototipos;

Definicion_particula_movil_base::Definicion_particula_movil_base(float x, float y, float tv, const DLibH::Vector_2d v)
	:Definicion_particula(x, y, tv), 
	v(v)
{

} 
