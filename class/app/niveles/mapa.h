#ifndef MAPA_H
#define MAPA_H

#include "sala.h"

namespace App_Niveles
{

class Mapa
{
	private:

	unsigned int w, h;
	Matriz_2d<Sala> salas;

	///////////
	// Interface pública.

	public:

	Mapa(unsigned int pw, unsigned int ph)
		:w(pw), h(ph),
		salas(w, h)
	{}

	unsigned int acc_w() const {return w;}
	unsigned int acc_h() const {return h;}

	/**
	* @throw Matriz_2d_excepcion_item_existe
	*/

	void insertar_sala(unsigned int px, unsigned py, Sala& sala)
	{
		salas.insert(px, py, sala);
	}

	/**
	* @throw Matriz_2d_excepcion_item_existe
	*/

	Sala& obtener_sala(unsigned int px, unsigned int py)
	{
		return salas(px, py);
	}
};

}

#endif
