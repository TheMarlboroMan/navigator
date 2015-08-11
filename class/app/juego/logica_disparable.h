#ifndef LOGICA_DISPARABLE_H
#define LOGICA_DISPARABLE_H

#include "../interfaces/disparable_i.h"
#include "objetos_juego/proyectil_base.h"
#include <memory>
#include <vector>

/**
* Lógica para los objetos que implementen la interface "Disparable_I".
* Controla si han recibido impactos.
*/

namespace App_Juego
{

class Logica_disparable
{
	////////////////////////
	//Interface pública.
	public:

				Logica_disparable(std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base> >&);
	virtual void 		procesar(std::vector<std::shared_ptr<App_Interfaces::Disparable_I>>&);

	/////////////////////////
	//Propiedades privadas.
	private:

	std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base> >& proyectiles_jugador;
};
}

#endif
