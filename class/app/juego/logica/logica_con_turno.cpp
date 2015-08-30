#include "logica_con_turno.h"

using namespace App_Juego_Logica;

Logica_con_turno::Logica_con_turno(App_Interfaces::Contexto_turno_I& c)
	:contexto(c)
{

}

void Logica_con_turno::procesar(std::vector<App_Interfaces::Con_turno_I *>& v)
{
	for(auto& o : v)
	{
		if(!o->es_borrar()) 
		{
			o->turno(contexto);
		}
	}
}
