#include "particula_fantasma.h"

using namespace App_Juego_ObjetoJuego;

Particula_fantasma::Particula_fantasma(float x, float y, float tv, float ve, App_Definiciones::direcciones direccion)
	:App_Interfaces::Objeto_juego_I(),
	Particula_base(tv),
	x(x), y(y), w(25.0f), h(14.0f), velocidad_expansion(ve),
	tiempo_vida_total(tv), direccion(direccion)
{

}

unsigned short int Particula_fantasma::obtener_profundidad_ordenacion()const
{
	return 25;
}

void Particula_fantasma::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::TR_BITMAP);

	if(es_expirada())
	{
		b.ocultar();
	}
	else
	{
		float alpha=(acc_tiempo_vida() * 192.0f) / tiempo_vida_total;
		if(alpha < 0.0f) alpha=0.0f;

		b.establecer_alpha(alpha);
		b.establecer_recurso(App::Recursos_graficos::RT_DEFECTO);
		b.establecer_recorte(32, 0, 27, 16);
		b.establecer_posicion(x, y, w, h);
		b.invertir_horizontal(direccion==App_Definiciones::direcciones::izquierda);
	}
}

void Particula_fantasma::turno(float delta)
{
	restar_tiempo_vida(delta);

	if(es_expirada())
	{
		mut_borrar(true);
	}
	else
	{
		float dist=delta * velocidad_expansion;
		w+=dist;
		h+=dist;
		x-=dist / 2.0f;
		y-=dist / 2.0f;
	}
}
