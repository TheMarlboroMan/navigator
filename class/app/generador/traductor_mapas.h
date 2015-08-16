#ifndef TRADUCTOR_MAPAS_H
#define TRADUCTOR_MAPAS_H

/**
* Esta clase convierte un vector de protosalas en un objeto Nivel completo.
*
*/

#include "proto_sala.h"
#include "../niveles/mapa.h"
#include "../definiciones/definiciones.h"
#include "../repositorio_salas/repositorio_salas.h"

namespace App_Generador
{
class Traductor_mapas
{
	///////////////////
	//Interface pública
	public:

	/**
	* @param std::vector<Proto_sala> p
	* @return Mapa.
	* Se entiende que el vector de proto_salas ya está normalizado o 
	* el fallo que puede dar es de categoría.
	*/



	App_Niveles::Mapa 		traducir_mapa(const std::vector<Proto_sala>& p, App_RepositorioSalas::Repositorio_salas&);

	//////////////////
	//Métodos privados
	private:

	void				parsear_sala(const Proto_sala&, App_Niveles::Mapa&, App_RepositorioSalas::Repositorio_salas&);
};

}

#endif
