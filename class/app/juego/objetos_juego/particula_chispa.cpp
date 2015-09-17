#include "particula_chispa.h"

using namespace App_Juego_ObjetoJuego;

Particula_chispa::Particula_chispa(float x, float y, float tv, const DLibH::Vector_2d& v):
	Particula_movil_base(x, y, tv, v), cr(0), cg(0), cb(0), ca(0)
{
	auto G=Herramientas_proyecto::Generador_int(128, 255);
	cr=G();
	cg=G();
	cb=G();
	ca=G();
}

unsigned short int Particula_chispa::obtener_profundidad_ordenacion()const
{
	return 30;
}

unsigned int Particula_chispa::obtener_ciclos_representable()const
{
	return 1;
}

void Particula_chispa::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_primitiva_puntos);
	b.establecer_alpha(ca);
	b.establecer_color_puntos(cr, cg, cb);
	b.insertar_punto(acc_espaciable_x(), acc_espaciable_y());
}
