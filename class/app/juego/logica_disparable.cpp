#include "logica_disparable.h"

using namespace App_Juego;

Logica_disparable::Logica_disparable(std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base> >& pj)
	:proyectiles_jugador(pj)
{

}

void Logica_disparable::procesar(vector_oj v)
{
	for(auto& o : v)
	{
		if(es_disparable(*o) && es_espaciable(*o) && !o->es_borrar()) 
		{
			for(auto& p : proyectiles_jugador)
			{
				auto &f=o->como_facetador();
				if(!(p->es_borrar()) && f.espaciable->en_colision_con(*p))
				{
					f.disparable->recibir_disparo(p->acc_potencia());
					p->mut_borrar(true);
				}
			}
		}
	}
}
