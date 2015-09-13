#include "particula_fantasma.h"

using namespace App_Juego_ObjetoJuego;

Particula_fantasma::Particula_fantasma(float x, float y, float tv, float ve)
	:App_Interfaces::Objeto_juego_I(),
	Particula_base(tv),
	x(x), y(y), extra_w(0.0), extra_h(0.0),
	velocidad_expansion(ve)
{

}

unsigned short int Particula_fantasma::obtener_profundidad_ordenacion()const
{
	return 25;
}

void Particula_fantasma::turno(App_Interfaces::Contexto_turno_I& ct)
{
	auto delta=ct.acc_delta();
	restar_tiempo_vida(delta);

	float dist=delta * velocidad_expansion;
	extra_w+=dist;
	extra_h+=dist;
	x-=dist / 2.0f;
	y-=dist / 2.0f;
}
