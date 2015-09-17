#ifndef VISTA_UNIDAD_AUTOMAPA_H
#define VISTA_UNIDAD_AUTOMAPA_H

#include "../../interfaces/representable_i.h"
#include "../../graficos/bloque_transformacion_representable.h"
#include "../../recursos.h"
#include "unidad_automapa.h"

namespace App_Juego_Automapa
{
struct Vista_unidad_automapa:
	public Unidad_automapa,
	public App_Interfaces::Representable_I
{
	static int pos_x_automapa;
	static int pos_y_automapa;
	static int dim_celda_automapa;
	static const int DIM_RECORTE=7;
	mutable bool actual;

	int vista_x, vista_y;

	/**
	* El offset tiene como objetivo compensar la vista y que a la hora de
	* modificar los bloques representables el mapa esté siempre en la
	* misma posición (las vistas llevan x e y e intentarán usarla para 
	* colocarse en posición).
	*/

	Vista_unidad_automapa(const Unidad_automapa& u, int vx, int vy)
		:Unidad_automapa(u), actual(false),
		vista_x(vx), vista_y(vy)
	{}

	virtual unsigned int 			obtener_ciclos_representable() const {return 1;}
	virtual unsigned short int 		obtener_profundidad_ordenacion() const {return 0;}
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const;
	virtual bool				es_representable_borrar() const {return false;}
};
}

#endif
