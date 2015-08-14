#ifndef _REPOSITORIO_SALAS_H
#define _REPOSITORIO_SALAS_H

#include "../definiciones/definiciones.h"
#include <map>
#include <vector>
#include "item_repositorio.h"
#include "../generador/parser_salas.h"

namespace App_RepositorioSalas
{

class Repositorio_salas
{
	//////////////////////////
	//Interface pública.
	public:
					Repositorio_salas();
	void 				iniciar(const std::string&); /** throw std::runtime_error */
	const std::string		obtener_ruta_sala(App_Definiciones::direcciones);

	//////////////////////////
	//Internas.
	private:

	void 				iniciar_mapa();

	std::map<App_Definiciones::direcciones, std::vector<Item_repositorio> > mapa_rutas;

};

}

#endif
