#include "celda.h"

using namespace App_Niveles;

/**
* @param t_dim x
* @param t_dim y
* @param tipo_celda t
*/

Celda::Celda(App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py, tipo_celda pt)
		:x(px), y(py), tipo(pt)
{

}

void Celda::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
{
	using namespace App_Definiciones;
	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::TR_BITMAP);
	b.establecer_recurso(App::Recursos_graficos::RT_DEFECTO);
	b.establecer_posicion(x*tipos::DIM_CELDA, y*tipos::DIM_CELDA, tipos::DIM_CELDA, tipos::DIM_CELDA);
	b.establecer_recorte(0, 0, tipos::DIM_CELDA, tipos::DIM_CELDA);
}

App_Interfaces::Espaciable::t_caja Celda::copia_caja() const
{
	using namespace App_Definiciones;
	return App_Interfaces::Espaciable::t_caja(tipos::DIM_CELDA*x,tipos::DIM_CELDA*y,tipos::DIM_CELDA,tipos::DIM_CELDA);
}
