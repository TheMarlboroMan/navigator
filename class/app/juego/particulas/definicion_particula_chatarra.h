#ifndef DEFINICION_PARTICULA_CHATARRA_H
#define DEFINICION_PARTICULA_CHATARRA_H

#include "definicion_particula.h"
#include "../objetos_juego/particula_chatarra.h"
#include <herramientas/vector_2d/vector_2d.h>

namespace App_Juego_Particulas
{

//TODO: Comparte con la explosión TODA la definición excepto el método "crear
// partícula"... Probablemente esto se repita con otras partículas de modo
// que crearemos una base "particula_movil".

struct Definicion_particula_chatarra:
	public Definicion_particula
{
					Definicion_particula_chatarra(float x, float y, float tv, const DLibH::Vector_2d v);
	virtual sptrParticula	 	crear_particula();
	DLibH::Vector_2d		v;

};
}

#endif
