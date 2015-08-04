#ifndef LOGICA_PROYECTILES_H
#define LOGICA_PROYECTILES_H

#include <memory>
#include <vector>
#include "proyectiles/proyectil_normal.h"
#include "jugador.h"

namespace App_Juego
{

class Logica_proyectiles
{
	///////////////////////
	//Interface pública:
	public:

			Logica_proyectiles();
	bool 		insertar_disparo_jugador(std::vector<std::shared_ptr<App_Juego_Proyectiles::Proyectil_base> >&v, Jugador& j);

	///////////////////////
	//Propiedades:
	private:
};

}

#endif
