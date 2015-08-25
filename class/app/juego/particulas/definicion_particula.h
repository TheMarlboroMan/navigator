#ifndef DEFINICION_PARTICULA_H
#define DEFINICION_PARTICULA_H

#include <memory>

namespace App_Juego_ObjetoJuego
{
class Particula_base;
}

namespace App_Juego_Particulas
{
struct Definicion_particula
{
	typedef std::shared_ptr<App_Juego_ObjetoJuego::Particula_base> sptrParticula;

					Definicion_particula(float x, float y, float tv);
	virtual sptrParticula	 	crear_particula()=0;

	float 				x, y;
	float 				tiempo_vida;
};
}

#endif
