#ifndef PARTICULA_FANTASMA_BONUS_TIEMPO_H
#define PARTICULA_FANTASMA_BONUS_TIEMPO_H

#include "particula_fantasma.h"
#include "../../recursos.h"

namespace App_Juego_ObjetoJuego
{

class Particula_fantasma_bonus_tiempo:
	public Particula_fantasma
{
	////////////////////////
	//Interface pública.
	public:
				Particula_fantasma_bonus_tiempo(float x, float y, float tv, float ve);
				
	//////////////
	// Implementación de Representable_I
	public:

	virtual unsigned int 			obtener_ciclos_representable()const;
	virtual unsigned short int 		obtener_profundidad_ordenacion()const;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;

	/////////////////////////
	//Internas...,
	private:
};

}

#endif
