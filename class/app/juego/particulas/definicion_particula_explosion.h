#ifndef DEFINICION_PARTICULA_EXPLOSION_H
#define DEFINICION_PARTICULA_EXPLOSION_H

#include "definicion_particula.h"
#include "../objetos_juego/particula_explosion.h"

namespace App_Juego_Particulas
{

struct Definicion_particula_explosion:
	public Definicion_particula
{
					Definicion_particula_explosion(float x, float y, float tv, float vx, float vy);
	virtual sptrParticula	 	crear_particula();
	float			vx, vy;

};
}

#endif
