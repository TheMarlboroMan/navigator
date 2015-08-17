#include "celda_decorativa.h"

using namespace App_Niveles;

/**
* @param t_dim x
* @param t_dim y
*/

Celda_decorativa::Celda_decorativa(App_Definiciones::t_dim px, App_Definiciones::t_dim py, App_Definiciones::t_dim p_indice)
		:Celda_base(px, py), indice(p_indice)
{

}

void Celda_decorativa::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
{
	using namespace App_Definiciones;
	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::TR_BITMAP);
	b.establecer_recurso(App::Recursos_graficos::RT_DEFECTO);
	b.establecer_posicion(x*definiciones::dim_celda, y*definiciones::dim_celda, definiciones::dim_celda, definiciones::dim_celda);
	b.establecer_recorte(0, 0, definiciones::dim_celda, definiciones::dim_celda);
}

