#include "automapa.h"
#include <stdexcept>
#include <sstream>

using namespace App_Juego_Automapa;

#include <herramientas/log_base/log_base.h>
extern DLibH::Log_base LOG;

Automapa::Automapa()
	:x_jugador(0), y_jugador(0)
{

}

/**
* @param int pw : ancho del mapa con índice 0.
* @param int ph : alto del mapa con índice 0.
* Prerellena el vector con casillas vacías, simplemente
* para que estén ahí, en función del ancho y alto. 
* Cuando se busque uno que queda fuera va a dar excepciones...
*/

void Automapa::inicializar(int pw, int ph)
{
	//Vaciar las unidades...
	unidades.clear();

	for(int y=0; y < ph; ++y)
	{
		for(int x=0; x < pw; ++x)
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

	std::stringstream ss;
	ss<<"No se localiza la unidad de automapa "<<x<<","<<y;
	throw std::logic_error(ss.str());
}

Unidad_automapa Automapa::copia_unidad(int x, int y) const
{
	for(const Unidad_automapa& u : unidades)
	{
		if(u.x==x && u.y==y) return u;
	}

	return Unidad_automapa(x, y);
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

void Automapa::establecer_posicion_jugador(int px, int py)
{
	x_jugador=px;
	y_jugador=py;
}
