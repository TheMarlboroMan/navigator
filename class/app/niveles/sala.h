#ifndef SALA_H
#define SALA_H

#include "celda.h"
#include "entrada.h"
#include "../../herramientas_proyecto/matriz2d.h"
#include "../definiciones/definiciones.h"
#include <memory>
#include "../interfaces/objeto_juego_i.h"
#include "../interfaces/procesador_objetos_juego_i.h"

namespace App_Niveles
{

class Sala
{
	////////////
	// Definiciones internas.
	private:

	typedef std::shared_ptr<App_Interfaces::Objeto_juego_I> sptr_Objeto_juego_I;
	typedef std::vector<std::shared_ptr<App_Interfaces::Objeto_juego_I> > Vsptr_Objeto_juego_I;

	///////////
	// Propiedades

	private:

	App_Definiciones::tipos::coordenadas_t_dim 		pos; //Posición en una rejilla general.
	App_Definiciones::tipos::t_dim 				w, h;		//Ancho y alto.
	HerramientasProyecto::Matriz_2d<Celda> 			celdas;
	//TODO: Quizás podamos meter las entradas en los objetos de juego.
	std::vector<Entrada> 					entradas;
	App_Definiciones::direcciones 				direcciones_entradas;
	Vsptr_Objeto_juego_I					objetos_juego;	//Todos los objetos de juego van aquí.

	///////////
	// Interface pública.
	public:


								Sala(App_Definiciones::tipos::t_dim pw, App_Definiciones::tipos::t_dim ph, App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py);

	App_Definiciones::tipos::t_dim 				acc_x() const {return pos.x;}
	App_Definiciones::tipos::t_dim 				acc_y() const {return pos.y;}
	App_Definiciones::tipos::t_dim 				acc_w() const {return w;}
	App_Definiciones::tipos::t_dim 				acc_h() const {return h;}
	App_Definiciones::direcciones 				acc_direcciones_entradas() const 	{return direcciones_entradas;}
	void 							insertar_celda(App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py, Celda::tipo_celda pt); /** @throw Matriz_2d_excepcion_item_existe cuando la celda está ocupada. */
	void 							erase(App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py); /** @throw Matriz_2d_excepcion_item_invalido cuando no existe la celda. */
	std::vector<const App_Interfaces::Representable_I *> 	obtener_vector_representables() const;
	Vsptr_Objeto_juego_I&					acc_objetos_juego() {return objetos_juego;}
	void 							insertar_entrada(const Entrada& e); /** std::logic_error cuando existe una entrada en la posición. */
	const HerramientasProyecto::Matriz_2d<Celda>& 		acc_matriz() const {return celdas;}
	const Entrada& 						obtener_entrada_posicion(App_Definiciones::direcciones p); /** @throw std::logic_error cuando no hay entrada en esa posición. */
	void 							insertar_objeto_juego(std::shared_ptr<App_Interfaces::Objeto_juego_I> obj);
	size_t 							limpiar_objetos_juego_para_borrar();
	void							procesar_objetos_juego(App_Interfaces::Procesador_objetos_juego_I&);

	/*
	void							procesar_visitante_objetos_juego(App_Visitantes::Visitante_objeto_juego& v);
	void							procesar_visitante_objetos_juego_const(App_Visitantes::Visitante_objeto_juego_const& v) const;
	*/
	
};

}
#endif
