#include "contexto_turno_juego.h"

using namespace App_Juego_Logica;

Contexto_turno_juego::Contexto_turno_juego(float delta, const App_Niveles::Sala& sala, App_Interfaces::Espaciable& jugador)
	:delta(delta), sala(sala), jugador(jugador)
{

}


bool Contexto_turno_juego::es_fuera_sala(const App_Interfaces::Espaciable::t_caja& e) const
{
	App_Colisiones::Calculador_colisiones cc;
	return cc.es_fuera_de_sala(e, sala);
}

std::vector<const App_Interfaces::Espaciable *> Contexto_turno_juego::celdas_en_caja(const App_Interfaces::Espaciable::t_caja&e) const
{
	App_Colisiones::Calculador_colisiones cc;
	auto cel=cc.celdas_en_caja(e, sala);
	std::vector<const App_Interfaces::Espaciable *> res;
	for(auto& c: cel) res.push_back(c);
	return res;
}
