#ifndef PARTICULA_FANTASMA_H
#define PARTICULA_FANTASMA_H

#include "particula_base.h"
#include "../../graficos/bloque_transformacion_representable.h"

namespace App_Juego_ObjetoJuego
{
class Particula_fantasma:
	public Particula_base
{
	//////////////////////
	//Interface pública.
	public:
						Particula_fantasma(float x, float y, float tv, float ve);

	//////////////
	// Implementación de Representable_I
	public:

	virtual unsigned int 			obtener_ciclos_representable()const=0;
	virtual unsigned short int 		obtener_profundidad_ordenacion()const=0;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const=0;

	//////////////
	// Implementación de Con_turno_I
	public:

	virtual void 				turno(App_Interfaces::Contexto_turno_I&);

	/////////////////
	//Internas.
	protected:

	float					x, y, extra_w, extra_h;
	float 					velocidad_expansion;
};

}

#endif
