#include "posicion_inicial.h"

using namespace App_Juego_ObjetoJuego;

Posicion_inicial::Posicion_inicial(App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py)
		:x(px), y(py)
{

}

App_Interfaces::Espaciable::t_caja Posicion_inicial::copia_caja() const
{
	using namespace App_Definiciones;
	return App_Interfaces::Espaciable::t_caja(x, y,tipos::DIM_CELDA,tipos::DIM_CELDA);
}
