#include "actor_movil.h"

using namespace App_Juego;

void Actor_movil::ajustar(float pos, posiciones_ajuste tipo)
{
	switch(tipo)
	{
		case posiciones_ajuste::arriba: mut_y_caja(pos); break;
		case posiciones_ajuste::abajo:	mut_y_caja(pos-acc_espaciable_h()); break;
		case posiciones_ajuste::izquierda: mut_x_caja(pos); break;
		case posiciones_ajuste::derecha: mut_x_caja(pos-acc_espaciable_w()); break;
	}

	callback_ajuste(pos, tipo);
}
