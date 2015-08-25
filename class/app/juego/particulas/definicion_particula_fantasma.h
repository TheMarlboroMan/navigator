#ifndef DEFINICION_PARTICULA_FANTASMA_H
#define DEFINICION_PARTICULA_FANTASMA_H

#include "definicion_particula.h"
#include "../objetos_juego/particula_fantasma.h"

namespace App_Juego_Particulas
{
struct Definicion_particula_fantasma:
	public Definicion_particula
{
					Definicion_particula_fantasma(float x, float y, float tv, float ve);
	virtual sptrParticula	 	crear_particula();
	float				velocidad_expansion;
};
}

#endif
