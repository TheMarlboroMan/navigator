#include "actor_movil.h"

using namespace App_Juego;

/*
* @param float pos: punto en el espacio.
* @param posiciones_ajuste tipo: tipo de ajuste.
*
* Por tipo de ajuste se entiende el "lado que se ajusta":
* 	arriba: el Actor_movil esta bajo de algo y ajustamos su parte de arriba pos.
* 	abajo: el Actor_movil esta sobre de algo y ajustamos su parte de abajo pos.
* 	izquierda: el Actor_movil esta a la derecha de algo y ajustamos su parte de izquierda pos.
* 	derecha: el Actor_movil esta a la izquierda de algo y ajustamos su parte de derecha pos.
*/

void Actor_movil::ajustar(float pos, posiciones_ajuste tipo)
{
	switch(tipo)
	{
		case posiciones_ajuste::arriba: 	mut_y_caja(pos); break;
		case posiciones_ajuste::abajo:		mut_y_caja(pos-acc_espaciable_h()); break;
		case posiciones_ajuste::izquierda: 	mut_x_caja(pos); break;
		case posiciones_ajuste::derecha: 	mut_x_caja(pos-acc_espaciable_w()); break;
		case posiciones_ajuste::nada:		return; break;
	}

	callback_ajuste(pos, tipo);
}

void Actor_movil::ajustar(const Espaciable& e, posiciones_ajuste tipo)
{
	float pos=0.0f;

	switch(tipo)
	{
		case posiciones_ajuste::arriba: 	pos=e.acc_espaciable_y()+e.acc_espaciable_h(); break;
		case posiciones_ajuste::abajo:		pos=e.acc_espaciable_y(); break;
		case posiciones_ajuste::izquierda: 	pos=e.acc_espaciable_x()+e.acc_espaciable_w(); break;
		case posiciones_ajuste::derecha: 	pos=e.acc_espaciable_x(); break;
		case posiciones_ajuste::nada:		return; break;
	}

	ajustar(pos, tipo);
}
