#include "definicion_particula_explosion.h"

using namespace App_Juego_Particulas;

Definicion_particula_explosion::Definicion_particula_explosion(float x, float y, float tv, float vx, float vy)
	:Definicion_particula(x, y, tv), 
	vx(vx), vy(vy)
{

} 

Definicion_particula::sptrParticula Definicion_particula_explosion::crear_particula()
{
	using namespace App_Juego_ObjetoJuego;
	sptrParticula resultado=sptrParticula(new Particula_explosion(x, y, tiempo_vida, DLibH::Vector_2d(vx, vy)));
	return resultado;
}
