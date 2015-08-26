#include "definicion_particula_explosion.h"

using namespace App_Juego_Particulas;

Definicion_particula_explosion::Definicion_particula_explosion(float x, float y, float tv, const DLibH::Vector_2d v)
	:Definicion_particula(x, y, tv), 
	v(v)
{

} 

Definicion_particula::sptrParticula Definicion_particula_explosion::crear_particula()
{
	using namespace App_Juego_ObjetoJuego;
	sptrParticula resultado=sptrParticula(new Particula_explosion(x, y, tiempo_vida, v));
	return resultado;
}
