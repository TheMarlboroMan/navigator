#ifndef SALA_H
#define SALA_H

#include "celda.h"
#include "entrada.h"
#include "../../herramientas_proyecto/matriz2d.h"
#include "../definiciones/definiciones.h"
#include <memory>

//Incluir los diversos tipos de objetos de mapa...
#include "../juego/objetos_juego/bonus_tiempo.h"

namespace App_Niveles
{

class Sala
{
	///////////
	// Propiedades

	private:

	App_Definiciones::tipos::coordenadas_t_dim 	pos; //Posición en una rejilla general.
	App_Definiciones::tipos::t_dim 			w, h;		//Ancho y alto.
	HerramientasProyecto::Matriz_2d<Celda> 		celdas;
	//TODO: Quizás podamos meter las entradas en los objetos de juego.
	std::vector<Entrada> 				entradas;
	App_Definiciones::direcciones 			direcciones_entradas;

	std::vector<std::shared_ptr<App_Interfaces::Objeto_juego_interface> >		objetos_juego;	//Todos los objetos de juego van aquí.

	///////////
	// Interface pública.

	public:

	/**
	* @param t_dim pw 
	* @param t_dim ph
	* @param t_dim px
	* @param t_dim py
	*/

	Sala(App_Definiciones::tipos::t_dim pw, 
		App_Definiciones::tipos::t_dim ph, 
		App_Definiciones::tipos::t_dim px, 
		App_Definiciones::tipos::t_dim py)
		:pos(px, py),
		w(pw), h(ph),
		celdas(pw, ph),
		direcciones_entradas(App_Definiciones::direcciones::nada)
	{}

	App_Definiciones::tipos::t_dim acc_x() const	 		{return pos.x;}
	App_Definiciones::tipos::t_dim acc_y() const	 		{return pos.y;}
	App_Definiciones::tipos::t_dim acc_w() const	 		{return w;}
	App_Definiciones::tipos::t_dim acc_h() const			{return h;}
	App_Definiciones::direcciones acc_direcciones_entradas() const 	{return direcciones_entradas;}

	/**
	* @param t_dim x
	* @param t_dim y
	* @param tipo_celda t
	* @throw Matriz_2d_excepcion_item_existe cuando la celda está ocupada.
	*/

	void insertar_celda(App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py, Celda::tipo_celda pt);

	/**
	* @param t_dim x
	* @param t_dim_y
	* @throw Matriz_2d_excepcion_item_invalido cuando no existe la celda.
	*/

	void erase(App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py);

	/**
	* @return std::vector<const Representable *>
	* Devuelve un vector con punteros a los objetos representables que contiene representables.
	*/
	
	std::vector<const App_Graficos::Representable *> obtener_vector_representables() const;

	/**
	* @param Entrada e
	* @throws TODO
	* Inserta una entrada en el vector de entradas. Se comprueba si se ha
	* intentado insertar una entrada para la misma posición antes, lo que
	* lanzaría la excepción.
	*/

	void insertar_entrada(const Entrada& e);

	/**
	* @return Matriz_2d<Celda>&
	* Este acceso a las internas está para facilitar el tema del cálculo de 
	* colisiones en otras clases. Lo podríamos reimaginar haciendo que esta 
	* clase reciba el calculador de colisiones y haciendo que le inyecte 
	* la información de turno.
	*/

	const HerramientasProyecto::Matriz_2d<Celda>& acc_matriz() const {return celdas;}

	/**
	* @return Entrada
	* @throw std::logic_error cuando no hay entrada en esa posición.
	*/

	const Entrada& obtener_entrada_posicion(App_Definiciones::direcciones p);

	void 		insertar_objeto_juego(std::shared_ptr<App_Interfaces::Objeto_juego_interface> obj);
	size_t 		limpiar_objetos_juego_para_borrar();
};

}
#endif
