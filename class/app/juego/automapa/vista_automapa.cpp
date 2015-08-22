#include "vista_automapa.h"

using namespace App_Juego_Automapa;

Vista_automapa::Vista_automapa(int pw, int ph)
	:w_vista(pw), h_vista(ph), 
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
	std::vector<const App_Interfaces::Representable_I *> res;
	auto &v=vista.front();
	v.pos_x_automapa=px;
	v.pos_y_automapa=py;
	v.dim_celda_automapa=pdim;
	for(auto& v : vista) res.push_back(&v);

	return res;
}

void Vista_automapa::refrescar_vista(const Automapa& am,int px, int py)
{
	vista.clear();

	//Calcular los límites...
	int ini_x=px-margen_w;
	int fin_x=ini_x + w_vista-1;

	int ini_y=py-margen_h;
	int fin_y=ini_y+h_vista-1;

	int vx=0, vy=0;

	int x_jugador=am.acc_x_jugador();
	int y_jugador=am.acc_y_jugador();

	for(int y=ini_y; y <= fin_y; ++y, ++vy)
	{
		vx=0;
		for(int x=ini_x; x <=fin_x; ++x, ++vx)
		{
			Vista_unidad_automapa vum(am.copia_unidad(x, y), vx, vy);
			vum.actual=vum.x==x_jugador && vum.y==y_jugador;
			vista.push_back(vum);
		}
	}
}
