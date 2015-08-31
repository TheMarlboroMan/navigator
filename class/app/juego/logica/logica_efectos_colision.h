#ifndef LOGICA_EFECTOS_COLISION_H
#define LOGICA_EFECTOS_COLISION_H

#include <vector>
#include "efecto_colision_recogedor.h"
#include "../../interfaces/efecto_colision_i.h"

namespace App_Juego_Logica
{

class Logica_efectos_colision
{
	/////////////////////////
	//Interface pública.

	public:
						Logica_efectos_colision(App_Juego_Sistemas::Contador_tiempo& t, App_Juego::Jugador& j);
	void					procesar(std::vector<App_Interfaces::Efecto_colision_I *>&);
	bool					es_salida_nivel() const {return false; /*TODO TODO*/;}
	/////////////////////////
	//Internas

	private:

	const App_Interfaces::Espaciable&	espaciable;
	Efecto_colision_recogedor		ecr;
};

}

#endif
