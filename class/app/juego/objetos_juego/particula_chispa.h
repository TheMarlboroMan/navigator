#ifndef PARTICULA_CHISPA_H
#define PARTICULA_CHISPA_H

#include <herramientas/vector_2d/vector_2d.h>

#include "particula_movil_base.h"
#include "../../../herramientas_proyecto/generador_numeros.h"

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

	virtual unsigned short int 		obtener_profundidad_ordenacion()const;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;

	//////////////
	// Implementación de Con_turno_I
	public:

	virtual void				recibir_visitante(App_Visitantes::Visitante_con_turno& v) {v.visitar(*this);}

	/////////////////
	//Internas.
	private:

	int 					cr, cg, cb, ca;
};
}

#endif