#ifndef PARTICULA_FANTASMA_JUGADOR_H
#define PARTICULA_FANTASMA_JUGADOR_H

#include "particula_fantasma.h"
#include "../../recursos.h"
#include "../../definiciones/definiciones.h"


namespace App_Juego_ObjetoJuego
{

class Particula_fantasma_jugador:
	public Particula_fantasma
{
	////////////////////////
	//Interface pública.
	public:
				Particula_fantasma_jugador(float x, float y, float tv, float ve, App_Definiciones::direcciones direccion);
				
	//////////////
	// Implementación de Representable_I
	public:

	virtual void 		transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;

	/////////////////////////
	//Internas...,
	private:

	App_Definiciones::direcciones 		direccion;
};

}

#endif
