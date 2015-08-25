#include "definicion_particula_explosion.h"

using namespace App_Juego_Particulas;

Definicion_particula_explosion::Definicion_particula_explosion(float x, float y, float tv, float vx, float vy)
	:Definicion_particula(x, y, tv), 
	vx(vx), vy(vy)
{

} 

Definicion_particula::sptrParticula Definicion_particula_explosion::crear_particula()
{
	//TODO TODO TODO
	sptrParticula resultado=sptrParticula(nullptr);
	return resultado;
}
