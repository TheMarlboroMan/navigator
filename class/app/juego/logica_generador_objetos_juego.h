#ifndef LOGICA_GENERADOR_OBJETOS_JUEGO_H
#define LOGICA_GENERADOR_OBJETOS_JUEGO_H

#include <memory>
#include <vector>
#include "../interfaces/generador_objetos_juego_i.h"
#include "../generador/factoria_objetos_juego.h"
#include "contenedores/contenedor_objetos.h"

namespace App_Juego
{

class Logica_generador_objetos_juego
{
	/////////////////////
	// Interface pública.

	public:

							Logica_generador_objetos_juego();
	void 						procesar(std::vector<std::shared_ptr<App_Interfaces::Generador_objetos_juego_I>> v);
	bool						hay_nuevos() const {return contenedor.objetos_juego.size();}
	App_Juego_Contenedores::Contenedor_objetos&	acc_contenedor() {return contenedor;}

	/////////////
	// Internas.

	private:

	App_Generador::Factoria_objetos_juego 		factoria;
	App_Juego_Contenedores::Contenedor_objetos 	contenedor;
};

}

#endif
