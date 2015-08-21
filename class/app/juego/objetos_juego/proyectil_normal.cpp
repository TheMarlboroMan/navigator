#include "proyectil_normal.h"
#include "../../recursos.h"

using namespace App_Juego_ObjetoJuego;

const float Proyectil_normal::FACTOR_DEBILITAR=9.0f;

Proyectil_normal::Proyectil_normal(const Propiedades_proyectil& pp)
	:Proyectil_base(pp.x, pp.y, pp.w, pp.h),
	color(colores::rojo)
{

}

void Proyectil_normal::turno(float delta)
{
	float p=acc_potencia();
	mut_potencia(p - (delta * FACTOR_DEBILITAR));

	if(acc_potencia() < 0.0f) 
	{
		mut_potencia(0.0f);
		mut_borrar(true);
	}

	//El movimiento está en el visitante de turno.
}

unsigned short int Proyectil_normal::obtener_profundidad_ordenacion()const
{
	return 40;
}

void Proyectil_normal::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	using namespace App_Graficos;
	using namespace App;

//	unsigned int alpha=(acc_potencia() * 255.0f) / acc_potencia_original();

	b.establecer_tipo(Bloque_transformacion_representable::tipos::TR_BITMAP);
//	b.establecer_alpha(alpha);
	b.establecer_recurso(Recursos_graficos::RT_DEFECTO);
	
	switch(color)
	{
		case colores::rojo: b.establecer_recorte(32, 16, acc_espaciable_w(), acc_espaciable_h()); break;
		case colores::azul: b.establecer_recorte(40, 16, acc_espaciable_w(), acc_espaciable_h()); break;
	}

	b.establecer_posicion(acc_espaciable_x(), acc_espaciable_y(), acc_espaciable_w(), acc_espaciable_h());
}
