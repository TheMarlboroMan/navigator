#ifndef DEFINICION_PARTICULA_CHATARRA_H
#define DEFINICION_PARTICULA_CHATARRA_H

#include "definicion_particula_movil_base.h"
#include "../objetos_juego/particula_chatarra.h"

namespace App_Juego_Particulas
{

struct Definicion_particula_chatarra:
	public Definicion_particula_movil_base
{
					Definicion_particula_chatarra(float x, float y, float tv, const DLibH::Vector_2d v);
	virtual sptrParticula	 	crear_particula();
};
}

#endif
