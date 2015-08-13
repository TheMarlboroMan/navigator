#ifndef SALA_H
#define SALA_H

#include "celda.h"
#include "../../herramientas_proyecto/matriz2d.h"
#include "../definiciones/definiciones.h"
#include <memory>

#include "../juego/objetos_juego/contenedor_objetos_juego.h"

namespace App_Niveles
{

class Sala
{
	///////////
	// Definiciones públicas.
	public:

	typedef std::shared_ptr<App_Interfaces::Objeto_juego_I> sptr_Objeto_juego_I;
	typedef std::vector<std::shared_ptr<App_Interfaces::Objeto_juego_I> > Vsptr_Objeto_juego_I;
	
	///////////
	// Interface pública.
	public:
								Sala(App_Definiciones::tipos::t_dim pw, App_Definiciones::tipos::t_dim ph, App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py);

	App_Definiciones::tipos::t_dim 				acc_x() const {return pos.x;}
	App_Definiciones::tipos::t_dim 				acc_y() const {return pos.y;}
	App_Definiciones::tipos::t_dim 				acc_w() const {return w;}
	App_Definiciones::tipos::t_dim 				acc_h() const {return h;}
	App_Definiciones::direcciones 				acc_direcciones_entradas() const 	{return objetos.direcciones_entradas;}
	void 							insertar_celda(App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py, Celda::tipo_celda pt); /** @throw Matriz_2d_excepcion_item_existe cuando la celda está ocupada. */
	void 							erase(App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py); /** @throw Matriz_2d_excepcion_item_invalido cuando no existe la celda. */
	void 							modificar_posicion_y_dimensiones(App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py, App_Definiciones::tipos::t_dim pw, App_Definiciones::tipos::t_dim ph);
	std::vector<const App_Interfaces::Representable_I *> 	obtener_vector_representables() const;
//	App_Juego_ObjetoJuego::Contenedor_objetos&		acc_contenedor_objetos() {return objetos;}
//	const App_Juego_ObjetoJuego::Contenedor_objetos&	acc_contenedor_objetos_const() const {return objetos;}
	void							implantar_objetos_juego(App_Juego_ObjetoJuego::Contenedor_objetos&&);
	const HerramientasProyecto::Matriz_2d<Celda>& 		acc_matriz() const {return celdas;}
	const App_Juego_ObjetoJuego::Entrada& 			obtener_entrada_posicion(App_Definiciones::direcciones p); /** @throw std::logic_error cuando no hay entrada en esa posición. */
	const App_Juego_ObjetoJuego::Posicion_inicial& 		obtener_posicion_inicial_jugador() {return objetos.posicion_inicial;}
	size_t 							limpiar_objetos_juego_para_borrar();

	template<typename T> void				procesar_objetos_juego(T& p) {p.procesar(objetos.objetos_juego);}
	template<typename T> void				procesar_bonus(T& p) {p.procesar(objetos.bonus);}
	template<typename T> void				procesar_con_turno(T& p) {p.procesar(objetos.con_turno);}
	template<typename T> void				procesar_disparables(T& p) {p.procesar(objetos.disparables);}
	template<typename T> void 				procesar_disparadores(T& p) {p.procesar(objetos.disparadores);}
	template<typename T> void				procesar_representables(T& p) {p.procesar(objetos.representables);}
	template<typename T> void				procesar_colisionables(T& p) {p.procesar(objetos.colisionables);}

	///////////
	// Propiedades

	private:

	App_Definiciones::tipos::coordenadas_t_dim 		pos; //Posición en una rejilla general.
	App_Definiciones::tipos::t_dim 				w, h;		//Ancho y alto.
	HerramientasProyecto::Matriz_2d<Celda> 			celdas;
	App_Juego_ObjetoJuego::Contenedor_objetos	 	objetos;

	///////////
	// Métodos privados.
	private:

	template<typename T> size_t ayudante_borrar(std::vector<std::shared_ptr<T>>& v)
	{
		size_t	res=0;
		auto 	ini=std::begin(v),
			fin=std::end(v);
	
		while(ini < fin)
		{
			if(ini->get()->es_borrar())
			{
				ini=v.erase(ini);
				fin=std::end(v);
				++res;
			}
			else
			{
				++ini;
			}		
		}
		return res;
	}

};

}
#endif
