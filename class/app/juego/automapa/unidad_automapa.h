#ifndef UNIDAD_AUTOMAPA_H
#define UNIDAD_AUTOMAPA_H

#include "../../definiciones/definiciones.h"

namespace App_Juego_Automapa
{
struct Unidad_automapa
{
	int x, y;
	App_Definiciones::direcciones tipo;
	bool visitado;

	bool operator<(const Unidad_automapa& u) const
	{
		if(y < u.y) return true;
		else if(y > u.y) return false;
		else return x < u.x;
	}

	Unidad_automapa(int px, int py)
		:x(px), y(py), tipo(App_Definiciones::direcciones::nada), visitado(false)
	{}

	Unidad_automapa(const Unidad_automapa& o)
		:x(o.x), y(o.y), tipo(o.tipo), visitado(o.visitado)
	{}
};
}

#endif
