#include "sala.h"

using namespace App_Niveles;
using namespace HerramientasProyecto;

/**
* @param t_dim pw 
* @param t_dim ph
* @param t_dim px
* @param t_dim py
*/

Sala::Sala(App_Definiciones::t_dim pw, App_Definiciones::t_dim ph, App_Definiciones::t_dim px, App_Definiciones::t_dim py)
	:pos(px, py), w(pw), h(ph), 
	//TODO: Esconder estas dos detrás de una clase más...
	celdas(pw, ph), celdas_decorativas(pw, ph)
{

}

/**
* @param t_dim x
* @param t_dim y
* @param tipo_celda t
* @throw Matriz_2d_excepcion_item_existe cuando la celda está ocupada.
*/

void Sala::insertar_celda(App_Definiciones::t_dim px, App_Definiciones::t_dim py, Celda::tipo_celda pt)
{
	celdas(px, py, Celda(px, py, pt));
}

void Sala::insertar_celda_decorativa(App_Definiciones::t_dim px, App_Definiciones::t_dim py, App_Definiciones::t_dim pi)
{
	celdas_decorativas(px, py, Celda_decorativa(px, py, pi));
}

/**
* @return std::vector<const Representable *>
* Devuelve un vector con punteros a los objetos representables que contiene representables.
*/

std::vector<const App_Interfaces::Representable_I *> Sala::obtener_vector_representables() const
{
	using namespace App_Interfaces;

	typedef std::vector<const App_Interfaces::Representable_I *> t_res;
	t_res resultado;

	struct obtener
	{		
		obtener(t_res& res):r(res) {}
		t_res& r;
		void operator()(const Celda_decorativa& c) {r.push_back(&c);}
	}obt(resultado);

	//Recolectar las celdas.
	celdas_decorativas.aplicar(obt);

	//Recolectar los objetos juego.
	for(auto& o : objetos.representables) resultado.push_back(o.get());

	return resultado;
}

std::vector<App_Interfaces::Sonoro_I *> Sala::obtener_vector_sonoros() const
{
	std::vector<App_Interfaces::Sonoro_I *> resultado;
	for(auto& o : objetos.sonoros) resultado.push_back(o.get());
	return resultado;
}

/**
* @return Entrada
* @throw std::logic_error cuando no hay entrada en esa posición.
*/

const App_Juego_ObjetoJuego::Entrada& Sala::obtener_entrada_posicion(App_Definiciones::direcciones p)
{
	for(const auto& e : objetos.entradas)
	{
		if(e.acc_posicion()==p) return e;
	}
	throw std::logic_error("No hay entrada en la posición establecida");
}

/**
* @return size_t : indicando el número de elementos eliminados.
*/

size_t Sala::limpiar_objetos_juego_para_borrar()
{
	return objetos.limpiar_para_borrar();
}

void Sala::modificar_posicion(App_Definiciones::t_dim px, App_Definiciones::t_dim py)
{
	pos.x=px;
	pos.y=py;
}

void Sala::modificar_dimensiones(App_Definiciones::t_dim pw, App_Definiciones::t_dim ph)
{
	w=pw;
	h=ph;
	//TODO: Esconder estas dos detrás de una clase más...
	celdas=celdas.copiar_con_dimensiones(w, h);
	celdas_decorativas=celdas_decorativas.copiar_con_dimensiones(w, h);
}

void Sala::implantar_objetos_juego(App_Juego_Contenedores::Contenedor_objetos&& co)
{
	objetos=co;
}

void Sala::fusionar_objetos_juego(App_Juego_Contenedores::Contenedor_objetos& co)
{
	objetos.fusionar_con(co);
}
