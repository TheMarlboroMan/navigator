#include "contenedor_objetos_juego.h"

using namespace App_Juego_ObjetoJuego;

Contenedor_objetos::Contenedor_objetos()
	:
	posicion_inicial(32, 32),
	direcciones_entradas(App_Definiciones::direcciones::nada)
{

}


/**
* @param Entrada e
* @throws std::logic_error cuando existe una entrada en la posición.
* Inserta una entrada en el vector de entradas. Se comprueba si se ha
* intentado insertar una entrada para la misma posición antes, lo que
* lanzaría la excepción.
*/

void Contenedor_objetos::insertar_entrada(const Entrada& e)
{
	using namespace App_Definiciones;

	if( (direcciones_entradas & e.acc_posicion() ) != direcciones::nada)
	{
		throw std::logic_error("Ya existe una entrada en la posición indicada");
	}
	
	entradas.push_back(e);
	direcciones_entradas=direcciones_entradas | e.acc_posicion();
}
