#ifndef LOGICA_CON_TURNO_H
#define LOGICA_CON_TURNO_H

#include <vector>
#include "../../interfaces/contexto_turno_i.h"
#include "../../interfaces/con_turno_i.h"

namespace App_Juego_Logica
{
class Logica_con_turno
{
	///////////////////////
	//Interface pública.
	public:

						Logica_con_turno(App_Interfaces::Contexto_turno_I&);
	virtual void 				procesar(std::vector<App_Interfaces::Con_turno_I *>&);

	///////////////////////
	//Propiedades privadas
	private:

	App_Interfaces::Contexto_turno_I&	contexto;
};
}

#endif
