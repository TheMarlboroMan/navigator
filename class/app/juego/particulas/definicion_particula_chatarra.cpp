#include "definicion_particula_chatarra.h"

using namespace App_Juego_Particulas;

Definicion_particula_chatarra::Definicion_particula_chatarra(float x, float y, float tv, const DLibH::Vector_2d v)
	:Definicion_particula(x, y, tv), 
	v(v)
{

} 

Definicion_particula::sptrParticula Definicion_particula_chatarra::crear_particula()
{
	using namespace App_Juego_ObjetoJuego;
	sptrParticula resultado=sptrParticula(new Particula_chatarra(x, y, tiempo_vida, v));
	return resultado;
}
