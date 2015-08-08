#include "objeto_juego_i.h"

using namespace App_Interfaces;

Objeto_juego_I::Objeto_juego_I(const Facetador& f)
	:facetador(f), borrar(false)
{

}

Objeto_juego_I::Objeto_juego_I()
	:borrar(false)
{

}

bool App_Interfaces::es_representable(const Objeto_juego_I& oj)
{
	return oj.facetador.representable != nullptr;
}

bool App_Interfaces::es_espaciable(const Objeto_juego_I& oj)
{
	return oj.facetador.espaciable != nullptr;
}

bool App_Interfaces::es_con_turno(const Objeto_juego_I& oj)
{
	return oj.facetador.con_turno != nullptr;
}

bool App_Interfaces::es_bonus(const Objeto_juego_I& oj)
{
	return oj.facetador.bonus != nullptr;
}

bool App_Interfaces::es_disparable(const Objeto_juego_I& oj)
{
	return oj.facetador.disparable != nullptr;
}

bool App_Interfaces::es_disparador(const Objeto_juego_I& oj)
{
	return oj.facetador.disparador != nullptr;
}
