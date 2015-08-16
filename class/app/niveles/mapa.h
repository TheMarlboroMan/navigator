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

	App_Definiciones::t_dim 				w, h;
	App_Definiciones::tipos::coordenadas_t_dim 		sala_inicial;
	HerramientasProyecto::Matriz_2d<Sala> 			salas;

	///////////
	// Interface pública.

	public:

								Mapa(App_Definiciones::t_dim pw, App_Definiciones::t_dim ph);
	App_Definiciones::t_dim 				acc_w() const {return w;}
	App_Definiciones::t_dim 				acc_h() const {return h;}
	void 							insertar_sala(App_Definiciones::t_dim px, App_Definiciones::t_dim py, Sala& sala); 	/** @throw Matriz_2d_excepcion_item_existe @throw Matriz_2d_excepcion_fuera_limites */
	Sala& 							obtener_sala(App_Definiciones::t_dim px, App_Definiciones::t_dim py); 	/** @throw Matriz_2d_excepcion_item_no_existe */
	Sala& 							obtener_sala_inicio(); 	/** @throw Matriz_2d_excepcion_item_no_existe */
	void 							establecer_coordenadas_sala_inicial(App_Definiciones::t_dim px, App_Definiciones::t_dim py);

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
