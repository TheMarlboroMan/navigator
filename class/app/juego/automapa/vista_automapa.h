#ifndef VISTA_AUTOMAPA_H
#define VISTA_AUTOMAPA_H

#include <vector>
#include "vista_unidad_automapa.h"
#include "automapa.h"

/**
* Un objeto que contiene un array de vistas de automapa persistente de forma
* que puede existir dentro de cada controlador de forma independiente al mapa.
*/

namespace App_Juego_Automapa
{
class Vista_automapa
{
	/////////////////////////
	//Interface pública.
	public:

						Vista_automapa(int, int);

	void 					refrescar_vista(const App_Niveles::Mapa& m,int px, int py);
	void					establecer_posicion_jugador(int px, int py);
	std::vector<const App_Interfaces::Representable_I *>	obtener_vista(int px, int py, int pdim) const;

	/////////////////////////
	//Privados.
	private:

	std::vector<Vista_unidad_automapa> 	vista;
	
	int					w_vista, h_vista;
	int					x_jugador, y_jugador;
	int					margen_w, margen_h;
};
}

#endif
