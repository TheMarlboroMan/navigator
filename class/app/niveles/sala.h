#ifndef SALA_H
#define SALA_H

#include "celda.h"
#include "celda_decorativa.h"
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
								Sala(App_Definiciones::t_dim pw, App_Definiciones::t_dim ph, App_Definiciones::t_dim px, App_Definiciones::t_dim py);

	App_Definiciones::t_dim 				acc_x() const {return pos.x;}
	App_Definiciones::t_dim 				acc_y() const {return pos.y;}
	App_Definiciones::t_dim 				acc_w() const {return w;}
	App_Definiciones::t_dim 				acc_h() const {return h;}
	App_Definiciones::direcciones 				acc_direcciones_entradas() const 	{return objetos.direcciones_entradas;}
	void 							insertar_celda(App_Definiciones::t_dim px, App_Definiciones::t_dim py, Celda::tipo_celda pt); /** @throw Matriz_2d_excepcion_item_existe cuando la celda está ocupada. */
	void 							insertar_celda_decorativa(App_Definiciones::t_dim px, App_Definiciones::t_dim py, App_Definiciones::t_dim pi); /** @throw Matriz_2d_excepcion_item_existe cuando la celda está ocupada. */
	void 							modificar_posicion(App_Definiciones::t_dim px, App_Definiciones::t_dim py);
	void 							modificar_dimensiones(App_Definiciones::t_dim px, App_Definiciones::t_dim py);
	std::vector<const App_Interfaces::Representable_I *> 	obtener_vector_representables() const;
	void							implantar_objetos_juego(App_Juego_ObjetoJuego::Contenedor_objetos&&);
	//TODO: Elimianr...
	const HerramientasProyecto::Matriz_2d<Celda>& 		acc_matriz() const {return celdas;}
	const App_Juego_ObjetoJuego::Entrada& 			obtener_entrada_posicion(App_Definiciones::direcciones p); /** @throw std::logic_error cuando no hay entrada en esa posición. */
	const std::shared_ptr<App_Juego_ObjetoJuego::Posicion_inicial>	obtener_posicion_inicial_jugador() {return objetos.posicion_inicial;}
	const std::shared_ptr<App_Juego_ObjetoJuego::Salida>	obtener_salida() {return objetos.salida;}
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
	App_Definiciones::t_dim 				w, h;		//Ancho y alto.
	HerramientasProyecto::Matriz_2d<Celda> 			celdas;
	HerramientasProyecto::Matriz_2d<Celda_decorativa> 	celdas_decorativas;
	App_Juego_ObjetoJuego::Contenedor_objetos	 	objetos;

	///////////
	// Métodos privados.
	private:
};

}
#endif
