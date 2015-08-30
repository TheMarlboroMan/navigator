#include "particula_movil_base.h"

using namespace App_Juego_ObjetoJuego;

Particula_movil_base::Particula_movil_base(float x, float y, float tv, const DLibH::Vector_2d& v):
	App_Interfaces::Objeto_juego_I(),
	Particula_base(tv),
	App_Juego::Actor_movil(x, y, 1.0, 1.0),
	fuerza_frenado(0.0)
{
	establecer_vector(v);
}

unsigned short int Particula_movil_base::obtener_profundidad_ordenacion()const
{
	return 30;
}

void Particula_movil_base::turno(App_Interfaces::Contexto_turno_I& ct)
{
	float delta=ct.acc_delta();
	restar_tiempo_vida(delta);

	//El movimiento...
	desplazar(delta);

	//Frenar...
	if(fuerza_frenado) frenar(delta, fuerza_frenado);
}

float Particula_movil_base::obtener_peso() const
{
	return 0.0f;
}
float Particula_movil_base::obtener_max_velocidad_caida() const
{
	return 0.0f;
}

void Particula_movil_base::callback_ajuste(float pos, posiciones_ajuste tipo)
{
	//Nada de nada...
}
