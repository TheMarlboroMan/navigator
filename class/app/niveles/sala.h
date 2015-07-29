#ifndef SALA_H
#define SALA_H

#include "celda.h"
#include "../matriz2d.h"

namespace App_Niveles
{

class Sala
{
	///////////
	// Definiciones

	typedef unsigned int t_dim;

	///////////
	// Propiedades

	private:

	t_dim pos_x, pos_y; //Posición en una rejilla general.
	t_dim w, h;		//Ancho y alto.
	Matriz_2d<Celda> celdas;

	///////////
	// Interface pública.

	public:

	Sala(t_dim pw, t_dim ph, t_dim px, t_dim py)
		:pos_x(px), pos_y(py), 
		w(pw), h(ph),
		celdas(pw, ph)
	{}

	t_dim acc_x() const {return pos_x;}
	t_dim acc_y() const {return pos_y;}
	t_dim acc_w() const {return w;}
	t_dim acc_h() const {return h;}

	/**
	* @throw Matriz_2d_excepcion_item_existe
	*/

	void insertar_celda(Celda::t_dim px, Celda::t_dim py, Celda::tipo_celda pt)
	{
		celdas(px, py, Celda(px, py, pt));
	}

	void erase(Celda::t_dim px, Celda::t_dim py)
	{
		celdas.erase(px, py);
	}

	/**
	* Devuelve un vector con punteros a las celdas representables.
	*/
	
	std::vector<const App_Graficos::Representable *> obtener_vector_celdas_representables() const
	{
		struct obtener
		{
			std::vector<const App_Graficos::Representable *> r;
			void operator()(const Celda& c) {r.push_back(&c);}
		}obt;

		celdas.aplicar(obt);
		return obt.r;
	}

	//Este acceso a las internas está para facilitar el tema del cálculo de colisiones en otras clases.
	//Lo podríamos reimaginar haciendo que esta clase reciba el calculador de colisiones
	//y haciendo que le inyecte la información de turno.
	const Matriz_2d<Celda>& acc_matriz() const {return celdas;}
};

}
#endif
