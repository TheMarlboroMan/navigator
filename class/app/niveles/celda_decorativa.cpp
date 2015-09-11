#include "celda_decorativa.h"

using namespace App_Niveles;

//TODO: This is shit. Un error al cargar y nunca se logueará.
HerramientasProyecto::Tabla_sprites Celda_decorativa::tabla_sprites("data/hojas/template_hoja.dat");

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
	const auto& t=tabla_sprites.obtener(indice);

	using namespace App_Definiciones;
	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_recurso(App::Recursos_graficos::rt_template_tiles);
	b.establecer_posicion(x*definiciones::dim_celda, y*definiciones::dim_celda, definiciones::dim_celda, definiciones::dim_celda);
	b.establecer_recorte(t.x, t.y, t.w, t.h);
}

