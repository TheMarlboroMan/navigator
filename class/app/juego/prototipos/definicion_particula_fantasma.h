#ifndef DEFINICION_PARTICULA_FANTASMA_H
#define DEFINICION_PARTICULA_FANTASMA_H

#include <herramientas/caja/caja.h>
#include "../../definiciones/definiciones.h"
#include "definicion_particula.h"
#include "../objetos_juego/particula_fantasma.h"

namespace App_Juego_Prototipos
{
struct Definicion_particula_fantasma:
	public Definicion_particula
{
					Definicion_particula_fantasma(float x, float y, float tv, float ve, App_Definiciones::direcciones d, int recurso, const DLibH::Caja<int, int>& recorte);
	virtual sptrParticula	 	crear_particula();
	float				velocidad_expansion;
	App_Definiciones::direcciones 	direccion;
	int				recurso;
	DLibH::Caja<int, int>		recorte;
};

std::shared_ptr<App_Juego_Prototipos::Definicion_particula> crear_particula_fantasma(float x, float y, float tv, float ve, App_Definiciones::direcciones d, int recurso, const DLibH::Caja<int, int>& recorte);
}

#endif
