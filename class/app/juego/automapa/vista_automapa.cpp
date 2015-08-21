#include "vista_automapa.h"

using namespace App_Juego_Automapa;

Vista_automapa::Vista_automapa(int pw, int ph)
	:w_vista(pw), h_vista(ph), 
	x_jugador(0), y_jugador(0),
	margen_w(w_vista/2), margen_h(h_vista/2)
{
	if(! (w_vista % 2) || !(h_vista % 2))
	{
		throw new std::runtime_error("La vista de automapa debe inicializarse con valores impares");
	}
}

/**
* @param int px: posición x del automapa.
* @param int py: posición y del automapa.
* @param int pdim: dimensión de la celda.
*/

std::vector<const App_Interfaces::Representable_I *> Vista_automapa::obtener_vista(int px, int py, int pdim) const
{
	//TODO: A cada uno de ellos darle el desplazamiento necesario, of course.
	std::vector<const App_Interfaces::Representable_I *> res;
	auto &v=vista.front();
	v.pos_x_automapa=px;
	v.pos_y_automapa=py;
	v.dim_celda_automapa=pdim;

	for(auto& v : vista) 
	{
		v.actual=v.x==x_jugador && v.y==y_jugador;
		res.push_back(&v);
	}

	return res;
}

void Vista_automapa::refrescar_vista(const App_Niveles::Mapa& m,int px, int py)
{
	vista.clear();

	//Calcular los límites...
	int ini_x=px-margen_w;
	int fin_x=ini_x + w_vista-1;

	int ini_y=py-margen_h;
	int fin_y=ini_y+h_vista-1;

	int vx=0, vy=0;

	for(int y=ini_y; y <= fin_y; ++y, ++vy)
	{
		vx=0;
		for(int x=ini_x; x <=fin_x; ++x, ++vx)
		{
			//TODO: esto puede lanzar excepciones.
			vista.push_back(Vista_unidad_automapa(m.obtener_unidad(x, y), vx, vy));
		}
	}
}

void Vista_automapa::establecer_posicion_jugador(int px, int py)
{
	x_jugador=px;
	y_jugador=py;
}
