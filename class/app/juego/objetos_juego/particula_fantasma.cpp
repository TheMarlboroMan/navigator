#include "particula_fantasma.h"

using namespace App_Juego_ObjetoJuego;

Particula_fantasma::Particula_fantasma(float x, float y, float tv, float ve, App_Definiciones::direcciones direccion, int recurso, const DLibH::Caja<int, int>& recorte)
	:App_Interfaces::Objeto_juego_I(),
	Particula_base(tv),
	x(x), y(y), w(recorte.w), h(recorte.h),
	velocidad_expansion(ve),
	direccion(direccion),
	recurso(recurso),
	recorte(recorte)	
{

}

unsigned short int Particula_fantasma::obtener_profundidad_ordenacion()const
{
	return 25;
}

void Particula_fantasma::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_bitmap);

	float alpha=calcular_parcial_tiempo_vida(192);
	if(alpha < 0.0f) alpha=0.0f;

	b.establecer_alpha(alpha);
	b.establecer_recurso(recurso);
	b.establecer_recorte(recorte.origen.x, recorte.origen.y, recorte.w, recorte.h);
	b.establecer_posicion(x, y, w, h);
	b.invertir_horizontal(direccion==App_Definiciones::direcciones::izquierda);
}

void Particula_fantasma::turno(App_Interfaces::Contexto_turno_I& ct)
{
	auto delta=ct.acc_delta();
	restar_tiempo_vida(delta);

	float dist=delta * velocidad_expansion;
	w+=dist;
	h+=dist;
	x-=dist / 2.0f;
	y-=dist / 2.0f;
}
