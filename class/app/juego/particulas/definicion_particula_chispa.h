#ifndef DEFINICION_PARTICULA_CHISPA_H
#define DEFINICION_PARTICULA_CHISPA_H

#include "definicion_particula_movil_base.h"
#include "../objetos_juego/particula_chispa.h"

namespace App_Juego_Particulas
{

struct Definicion_particula_chispa:
	public Definicion_particula_movil_base
{
					Definicion_particula_chispa(float x, float y, float tv, const DLibH::Vector_2d v);
	virtual sptrParticula	 	crear_particula();
};
}

#endif
