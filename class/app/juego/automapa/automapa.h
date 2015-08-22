#ifndef AUTOMAPA_H
#define AUTOMAPA_H

/**
* El automapa guarda la estructura completa del mapa en Unidad_automapa, que
* es cada una de las salas. Cualquier casilla, tenga o no tenga algo, guarda
* su tipo y su posición.
* Usando el automapa se pueden marcar las salas visitadas. Con cada visita se
* puede refrescar la vista del automapa para cambiar el centro y mostrar las
* nuevas casillas.
* Al solicitar una vista del automapa se devuelve un vector de UnidadAutomapa
* que representa una rejilla de ANCHO*ALTO.
*/

#include <vector>
#include <algorithm>
#include "unidad_automapa.h"

namespace App_Juego_Automapa
{
class Automapa
{
	/////////////
	//Interface pública
	public:

						Automapa();
	void 					inicializar(int pw, int ph);
	void 					descubrir(int px, int py);
	void					configurar(int px, int py, App_Definiciones::direcciones pt);
	Unidad_automapa 			copia_unidad(int x, int y)const;
	void					establecer_posicion_jugador(int px, int py);
	int					acc_x_jugador() const {return x_jugador;}
	int					acc_y_jugador() const {return y_jugador;}

	/////////////
	//Privados...

	private:
	std::vector<Unidad_automapa> 		unidades;
	int					x_jugador, y_jugador;
	Unidad_automapa& 			localizar(int x, int y);

};
}
#endif
