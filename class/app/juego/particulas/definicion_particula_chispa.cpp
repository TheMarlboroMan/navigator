#include "definicion_particula_chispa.h"

using namespace App_Juego_Particulas;

Definicion_particula_chispa::Definicion_particula_chispa(float x, float y, float tv, const DLibH::Vector_2d v)
	:Definicion_particula_movil_base(x, y, tv, v)
{

} 

Definicion_particula::sptrParticula Definicion_particula_chispa::crear_particula()
{
	using namespace App_Juego_ObjetoJuego;
	sptrParticula resultado=sptrParticula(new Particula_chispa(x, y, tiempo_vida, v));
	return resultado;
}
