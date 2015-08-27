#include "generador_particulas_i.h"

using namespace App_Interfaces;

//Declaración.

bool Generador_particulas_I::hay_particulas()
{
	return prototipos.size();
}

void Generador_particulas_I::reset_particulas()
{
	prototipos.clear();
}

void Generador_particulas_I::insertar_particula(sptrDefinicionParticula d)
{
	prototipos.push_back(d);
}

Generador_particulas_I::vDefinicionParticula& Generador_particulas_I::acc_particulas()
{
	return prototipos;
}
