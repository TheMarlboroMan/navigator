#include "celda.h"

using namespace App_Niveles;

/**
* @param t_dim x
* @param t_dim y
* @param tipo_celda t
*/

Celda::Celda(App_Definiciones::t_dim px, App_Definiciones::t_dim py, tipo_celda pt)
		:x(px), y(py), tipo(pt)
{

}

void Celda::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
{
	using namespace App_Definiciones;
	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::TR_BITMAP);
	b.establecer_recurso(App::Recursos_graficos::RT_DEFECTO);
	b.establecer_posicion(x*definiciones::dim_celda, y*definiciones::dim_celda, definiciones::dim_celda, definiciones::dim_celda);
	b.establecer_recorte(0, 0, definiciones::dim_celda, definiciones::dim_celda);
}

App_Interfaces::Espaciable::t_caja Celda::copia_caja() const
{
	using namespace App_Definiciones;
	return App_Interfaces::Espaciable::t_caja(definiciones::dim_celda*x,definiciones::dim_celda*y,definiciones::dim_celda,definiciones::dim_celda);
}
