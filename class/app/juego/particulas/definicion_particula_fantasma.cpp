#include "definicion_particula_fantasma.h"

using namespace App_Juego_Particulas;

Definicion_particula_fantasma::Definicion_particula_fantasma(float x, float y, float tv, float ve, App_Definiciones::direcciones d)
	:Definicion_particula(x, y, tv), velocidad_expansion(ve), direccion(d)
{

}

Definicion_particula::sptrParticula Definicion_particula_fantasma::crear_particula()
{
	using namespace App_Juego_ObjetoJuego;
	sptrParticula resultado=sptrParticula(new Particula_fantasma(x, y, tiempo_vida, velocidad_expansion, direccion));
	return resultado;
}
