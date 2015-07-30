#include "automapa.h"
#include <stdexcept>

using namespace App_Juego_Automapa;

void Automapa::inicializar(int pw, int ph)
{
	//Vaciar las unidades...
	unidades.clear();

	//Calcular los límites...
	int ini_x=-Definiciones_automapa::MARGEN_ANCHO;
	int fin_x=pw+Definiciones_automapa::MARGEN_ANCHO;

	int ini_y=-Definiciones_automapa::MARGEN_ALTO;
	int fin_y=ph+Definiciones_automapa::MARGEN_ALTO;

	for(int y=ini_y; y <= fin_y; ++y)
	{
		for(int x=ini_x; x <=fin_x; ++x)
		{
			unidades.push_back(Unidad_automapa(x, y));
		}
	}
}

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

void Automapa::configurar(int px, int py, App_Definiciones::direcciones pt)
{
	localizar(px, py).tipo=pt;
}

void Automapa::refrescar_vista(int px, int py)
{
	vista.clear();

	//Calcular los límites...
	int ini_x=px-Definiciones_automapa::MARGEN_ANCHO;
	int fin_x=ini_x + Definiciones_automapa::ANCHO-1;

	int ini_y=py-Definiciones_automapa::MARGEN_ALTO;
	int fin_y=ini_y+Definiciones_automapa::ALTO-1;

	for(int y=ini_y; y <= fin_y; ++y)
	{
		for(int x=ini_x; x <=fin_x; ++x)
		{
			auto copia=localizar(x, y);
			vista.push_back(copia);			
		}
	}
}
