#include "generador_particulas_i.h"

using namespace App_Interfaces;

//Declaración.
Generador_particulas_I::vDefinicionParticula Generador_particulas_I::prototipos;

bool Generador_particulas_I::hay_prototipos()
{
	return prototipos.size();
}

void Generador_particulas_I::reset_prototipos()
{
	prototipos.clear();
}

void Generador_particulas_I::insertar_prototipo(sptrDefinicionParticula d)
{
	prototipos.push_back(d);
}
