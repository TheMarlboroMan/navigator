#include "definicion_particula_chispa.h"

using namespace App_Juego_Prototipos;

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

std::shared_ptr<App_Juego_Prototipos::Definicion_particula> App_Juego_Prototipos::crear_particula_chispa(float x, float y, float tv, const DLibH::Vector_2d v)
{
	auto ptr=std::shared_ptr<Definicion_particula>(new Definicion_particula_chispa(x, y, tv, v));
	return ptr;
}
