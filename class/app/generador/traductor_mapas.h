#ifndef TRADUCTOR_MAPAS_H
#define TRADUCTOR_MAPAS_H

/**
* Esta clase convierte un vector de protosalas en un objeto Nivel completo.
*
*/

#include "proto_sala.h"
#include "../niveles/mapa.h"
#include "../definiciones/definiciones.h"

namespace App_Generador
{
class Traductor_mapas
{
	//////////////////
	//Métodos privados
	private:

	/**
	* @param Sala& sala
	* @param App_Definiciones::direcciones salida
	* Excava las salidas indicadas y rodea la sala con un muro.
	*/	

	static void muros_sala(App_Niveles::Sala& sala, App_Definiciones::direcciones salidas);

	/*
	* @param Sal& sala
	* Añade bloques aleatoriamente a la sala...
	*/

	static void obstaculos_sala(App_Niveles::Sala& sala);

	///////////////////
	//Interface pública
	public:

	Traductor_mapas() {}

	/**
	* @param std::vector<Proto_sala> p
	* @return Mapa.
	* Se entiende que el vector de proto_salas ya está normalizado o 
	* el fallo que puede dar es de categoría.
	*/

	App_Niveles::Mapa traducir_mapa(const std::vector<Proto_sala>& p);
};

}

#endif
