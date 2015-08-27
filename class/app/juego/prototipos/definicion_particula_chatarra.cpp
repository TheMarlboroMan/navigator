#include "definicion_particula_chatarra.h"

using namespace App_Juego_Prototipos;

Definicion_particula_chatarra::Definicion_particula_chatarra(float x, float y, float tv, const DLibH::Vector_2d v)
	:Definicion_particula_movil_base(x, y, tv, v)
{

} 

Definicion_particula::sptrParticula Definicion_particula_chatarra::crear_particula()
{
	using namespace App_Juego_ObjetoJuego;
	sptrParticula resultado=sptrParticula(new Particula_chatarra(x, y, tiempo_vida, v));
	return resultado;
}

std::shared_ptr<Definicion_particula> App_Juego_Prototipos::crea_particula_chatarra(float x, float y, float tv, const DLibH::Vector_2d v)
{
	auto ptr=std::shared_ptr<Definicion_particula>(new Definicion_particula_chatarra(x, y, tv, v));
	return ptr;
}
