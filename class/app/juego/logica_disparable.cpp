#include "logica_disparable.h"

using namespace App_Juego;

Logica_disparable::Logica_disparable(std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base >>& pj)
	:proyectiles_jugador(pj)
{

}

void Logica_disparable::procesar(std::vector<App_Interfaces::Disparable_I *>& v)
{
	for(auto& o : v)
	{
		for(auto& p : proyectiles_jugador)
		{
			if(!(p->es_borrar()) && o->es_colision_proyectil(*p))
			{
				o->recibir_disparo(p->acc_potencia());
				p->colisionar_con_enemigo(); //Implica borrar...
			}
		}
	}
}
