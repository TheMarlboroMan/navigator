#ifndef DEFINICION_PARTICULA_EXPLOSION_H
#define DEFINICION_PARTICULA_EXPLOSION_H

#include "definicion_particula.h"
#include "../objetos_juego/particula_explosion.h"
#include <herramientas/vector_2d/vector_2d.h>

namespace App_Juego_Particulas
{

struct Definicion_particula_explosion:
	public Definicion_particula
{
					Definicion_particula_explosion(float x, float y, float tv, const DLibH::Vector_2d v);
	virtual sptrParticula	 	crear_particula();
	DLibH::Vector_2d 		v;

};
}

#endif
