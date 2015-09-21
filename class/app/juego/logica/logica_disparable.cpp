#include "logica_disparable.h"

using namespace App_Juego_Logica;

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
				o->recibir_disparo(p->acc_potencia(), contexto);
				p->colisionar_con_enemigo(); //Implica borrar...
			}
		}
	}
}

void Logica_disparable::contexto::insertar_marcador(float val, float x, float y)
{
	size_t v=ceil(val);
	marcadores.push_back(marcador{v, x, y});
}

void Logica_disparable::contexto::generar_objetos(App_Interfaces::Factoria_objetos_juego_I& foj)
{
	for(const auto& m : marcadores)
	{
		foj.fabricar_particula_numero(m.x, m.y, m.numero);
	}
}
