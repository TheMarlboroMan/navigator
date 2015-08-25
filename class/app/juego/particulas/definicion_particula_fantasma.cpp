#include "definicion_particula_fantasma.h"

using namespace App_Juego_Particulas;

Definicion_particula_fantasma::Definicion_particula_fantasma(float x, float y, float tv, float ve)
	:Definicion_particula(x, y, tv), velocidad_expansion(ve)
{

}

Definicion_particula::sptrParticula Definicion_particula_fantasma::crear_particula()
{
	//TODO TODO TODO
	sptrParticula resultado=sptrParticula(nullptr);
	return resultado;
}
