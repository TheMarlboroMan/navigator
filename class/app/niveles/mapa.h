#ifndef MAPA_H
#define MAPA_H

#include "sala.h"

namespace App_Niveles
{

class Mapa
{
	///////////////
	// Propiedades
	private:

	App_Definiciones::tipos::t_dim w, h;
	App_Definiciones::tipos::coordenadas_t_dim sala_inicial;
	HerramientasProyecto::Matriz_2d<Sala> salas;

	///////////
	// Interface pública.

	public:

	Mapa(App_Definiciones::tipos::t_dim pw, App_Definiciones::tipos::t_dim ph)
		:w(pw), h(ph),
		sala_inicial(0, 0),
		salas(w, h)
	{}

	App_Definiciones::tipos::t_dim acc_w() const {return w;}
	App_Definiciones::tipos::t_dim acc_h() const {return h;}

	/**
	* @param t_dim x
	* @param t_dim y
	* @param Sala& sala
	* @throw Matriz_2d_excepcion_item_existe
	* @throw Matriz_2d_excepcion_fuera_limites
	*/

	void insertar_sala(App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py, Sala& sala)
	{
		salas.insert(px, py, sala);
	}

	/**
	* @param t_dim x
	* @param t_dim y
	* @throw Matriz_2d_excepcion_item_no_existe
	* @return Sala&
	*/

	Sala& obtener_sala(App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py)
	{
		return salas(px, py);
	}

	/**
	* @throw Matriz_2d_excepcion_item_no_existe
	* @return Sala&
	*/

	Sala& obtener_sala_inicio()
	{
		return salas(sala_inicial.x, sala_inicial.y);
	}

	void establecer_coordenadas_sala_inicial(App_Definiciones::tipos::t_dim px, 
				App_Definiciones::tipos::t_dim py)
	{
		sala_inicial.x=px;
		sala_inicial.y=py;
	}

	/**
	* Ejecuta el llamable l para cada una de las salas...
	*/

	template<typename Llamable> 
	void para_cada_sala(Llamable& l) const
	{
		salas.aplicar(l);
	}
};

}

#endif
