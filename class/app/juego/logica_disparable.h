#ifndef LOGICA_DISPARABLE_H
#define LOGICA_DISPARABLE_H

#include "../interfaces/procesador_objetos_juego_i.h"
#include "../interfaces/disparable_i.h"
#include "objetos_juego/proyectil_base.h"

/**
* Lógica para los objetos que implementen la interface "Disparable_I".
* Controla si han recibido impactos.
*/

namespace App_Juego
{
class Logica_disparable:
	public App_Interfaces::Procesador_objetos_juego_I
{
	////////////////////////
	//Interface pública.
	public:

				Logica_disparable(std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base> >&);

	////////////////////////
	//Implementación de Procesador_objetos_juego_I.
	virtual void 		procesar(vector_oj v);

	/////////////////////////
	//Propiedades privadas.
	private:

	std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base> >& proyectiles_jugador;
};
}

#endif
