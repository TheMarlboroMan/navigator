#ifndef DEFINICION_PARTICULA_MOVIL_BASE
#define DEFINICION_PARTICULA_MOVIL_BASE

#include "definicion_particula.h"
#include <herramientas/vector_2d/vector_2d.h>

/**
* Base para todas las definiciones de partículas que indican algo que se mueve.
*/

namespace App_Juego_Particulas
{

struct Definicion_particula_movil_base:
	public Definicion_particula
{
					Definicion_particula_movil_base(float x, float y, float tv, const DLibH::Vector_2d v);
	virtual sptrParticula	 	crear_particula()=0;
	DLibH::Vector_2d		v;

};
}
#endif
