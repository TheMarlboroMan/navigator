#include "mapa.h"

using namespace App_Niveles;

Mapa::Mapa(App_Definiciones::t_dim pw, App_Definiciones::t_dim ph)
	:w(pw), h(ph),
	sala_inicial(0, 0),
	salas(w, h)
{

}


/**
* @param t_dim x
* @param t_dim y
* @param Sala& sala
* @throw Matriz_2d_excepcion_item_existe
* @throw Matriz_2d_excepcion_fuera_limites
*/

void Mapa::insertar_sala(App_Definiciones::t_dim px, App_Definiciones::t_dim py, Sala& sala)
{
	salas.insert(px, py, sala);
}

/**
* @param t_dim x
* @param t_dim y
* @throw Matriz_2d_excepcion_item_no_existe
* @return Sala&
*/

Sala& Mapa::obtener_sala(App_Definiciones::t_dim px, App_Definiciones::t_dim py)
{
	return salas(px, py);
}

/**
* @throw Matriz_2d_excepcion_item_no_existe
* @return Sala&
*/

Sala& Mapa::obtener_sala_inicio()
{
	return salas(sala_inicial.x, sala_inicial.y);
}

void Mapa::establecer_coordenadas_sala_inicial(App_Definiciones::t_dim px, 
			App_Definiciones::t_dim py)
{
	sala_inicial.x=px;
	sala_inicial.y=py;
}

