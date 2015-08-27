#include "definicion_particula_fantasma.h"

using namespace App_Juego_Prototipos;

Definicion_particula_fantasma::Definicion_particula_fantasma(float x, float y, float tv, float ve, App_Definiciones::direcciones d, int recurso, const DLibH::Caja<int, int>& recorte)
	:Definicion_particula(x, y, tv), velocidad_expansion(ve), 
	direccion(d), recurso(recurso), recorte(recorte)
{

}

Definicion_particula::sptrParticula Definicion_particula_fantasma::crear_particula()
{
	using namespace App_Juego_ObjetoJuego;
	sptrParticula resultado=sptrParticula(new Particula_fantasma(x, y, tiempo_vida, velocidad_expansion, direccion, recurso, recorte));
	return resultado;
}

std::shared_ptr<Definicion_particula> App_Juego_Prototipos::crear_particula_fantasma(float x, float y, float tv, float ve, App_Definiciones::direcciones d, int recurso, const DLibH::Caja<int, int>& recorte)
{
	auto ptr=std::shared_ptr<Definicion_particula>(new Definicion_particula_fantasma(x, y, tv, ve, d, recurso, recorte));
	return ptr;
}
