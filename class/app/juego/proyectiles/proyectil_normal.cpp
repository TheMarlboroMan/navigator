#include "proyectil_normal.h"
#include "../../recursos.h"

using namespace App_Juego_Proyectiles;

/*Proyectil_normal::Proyectil_normal(float x, float y, unsigned int w, unsigned int h)
	:Proyectil_base(x, y, w, h)
{
}*/

Proyectil_normal::Proyectil_normal(const Propiedades_proyectil& pp)
	:Proyectil_base(pp.x, pp.y, pp.w, pp.h)
{

}

void Proyectil_normal::turno(float delta)
{
	auto v=acc_vector();
	if(v.y) desplazar_caja(0.0, v.y * delta); 
	if(v.x) desplazar_caja(v.x * delta, 0.0);
}

unsigned short int Proyectil_normal::obtener_profundidad_ordenacion()const
{
	return 10;

}

void Proyectil_normal::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	using namespace App_Graficos;
	using namespace App;

	//TODO...
	//Se asume que todos los frames van mirando a la derecha.
	b.establecer_tipo(Bloque_transformacion_representable::tipos::TR_BITMAP);
	b.establecer_alpha(255);
	b.establecer_recurso(Recursos_graficos::RT_DEFECTO);
	b.establecer_recorte(32, 0, acc_espaciable_w(), acc_espaciable_h());
	b.establecer_posicion(acc_espaciable_x(), acc_espaciable_y(), acc_espaciable_w(), acc_espaciable_h());
}
