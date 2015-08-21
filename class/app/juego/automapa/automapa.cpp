#include "automapa.h"
#include <stdexcept>

using namespace App_Juego_Automapa;

/**
* @param int pw : ancho del mapa
* @param int ph : alto del mapa
* Prerellena el vector con casillas vacías, simplemente
* para que estén ahí, en función del ancho y alto. Luego lo ordena.
* Mete más casillas del ancho real del mapa con la finalidad de acomodar
* espacios en blanco.
*/

void Automapa::inicializar(int pw, int ph)
{
	//Vaciar las unidades...
	unidades.clear();

	//Calcular los límites...
	int ini_x=-margen_w;
	int fin_x=pw+margen_w;

	int ini_y=-margen_h;
	int fin_y=ph+margen_h;

	for(int y=ini_y; y <= fin_y; ++y)
	{
		for(int x=ini_x; x <=fin_x; ++x)
		{
			unidades.push_back(Unidad_automapa(x, y));
		}
	}
}

/**
* @param int px
* @param int py
* Marca como descubierta la casilla en la posición dada. A partir de
* ese momento la casilla es ya visible.
*/


void Automapa::descubrir(int px, int py)
{
	localizar(px, py).visitado=true;
}

Unidad_automapa& Automapa::localizar(int x, int y)
{
	for(Unidad_automapa& u : unidades)
	{
		if(u.x==x && u.y==y) return u;
	}
	throw std::logic_error("No se localiza la unidad de automapa");
}

const Unidad_automapa& Automapa::obtener_unidad(int x, int y)
{
	for(Unidad_automapa& u : unidades)
	{
		if(u.x==x && u.y==y) return u;
	}
	throw std::logic_error("No se puede obtener la unidad de automapa");
}

/**
* @param int px
* @param int py
* @param App_Definiciones::direcciones pt
* Especifica el tipo de la celda indicada.
*/

void Automapa::configurar(int px, int py, App_Definiciones::direcciones pt)
{
	localizar(px, py).tipo=pt;
}
