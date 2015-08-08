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
/*
objeto_juego_facetas App_Interfaces::operator|(objeto_juego_facetas a, objeto_juego_facetas b)
{
	return static_cast<objeto_juego_facetas>(static_cast<int>(a) | static_cast<int>(b));
}

objeto_juego_facetas App_Interfaces::operator&(objeto_juego_facetas a, objeto_juego_facetas b)
{
	return static_cast<objeto_juego_facetas>(static_cast<int>(a) & static_cast<int>(b));
}
*/

bool App_Interfaces::es_representable(const Objeto_juego_I& oj)
{
//	return ( oj.obtener_facetas() & objeto_juego_facetas::representable) != objeto_juego_facetas::nada;
	return oj.como_facetador().representable != nullptr;
}

bool App_Interfaces::es_espaciable(const Objeto_juego_I& oj)
{
//	return ( oj.obtener_facetas() & objeto_juego_facetas::espaciable) != objeto_juego_facetas::nada;
	return oj.como_facetador().espaciable != nullptr;
}
/*
bool App_Interfaces::es_borrable(const Objeto_juego_I& oj)
{
	return ( oj.obtener_facetas() & objeto_juego_facetas::borrable) != objeto_juego_facetas::nada;
}
*/
bool App_Interfaces::es_con_turno(const Objeto_juego_I& oj)
{
//	return ( oj.obtener_facetas() & objeto_juego_facetas::con_turno) != objeto_juego_facetas::nada;
	return oj.como_facetador().con_turno != nullptr;
}

bool App_Interfaces::es_bonus(const Objeto_juego_I& oj)
{
//	return ( oj.obtener_facetas() & objeto_juego_facetas::bonus) != objeto_juego_facetas::nada;
	return oj.como_facetador().bonus != nullptr;
}
