#ifndef PARTICULA_CHISPA_H
#define PARTICULA_CHISPA_H

#include <herramientas/vector_2d/vector_2d.h>
#include <generador_numeros.h>
#include "particula_movil_base.h"

namespace App_Juego_ObjetoJuego
{
class Particula_chispa:
	public Particula_movil_base
{
	//////////////////
	//Interface pública...
	public:
						Particula_chispa(float x, float y, float tv, const DLibH::Vector_2d& v);

	//////////////
	// Implementación de Representable_I
	public:

	virtual unsigned int 			obtener_ciclos_representable()const;
	virtual unsigned short int 		obtener_profundidad_ordenacion()const;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;

	/////////////////
	//Internas.
	private:

	int 					cr, cg, cb, ca;
};
}

#endif
