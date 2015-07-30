#include "sala.h"

using namespace App_Niveles;
using namespace HerramientasProyecto;

/**
* @throw Matriz_2d_excepcion_item_existe cuando la celda está ocupada.
*/

void Sala::insertar_celda(App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py, Celda::tipo_celda pt)
{
	celdas(px, py, Celda(px, py, pt));
}

/**
* @throw Matriz_2d_excepcion_item_invalido cuando no existe la celda.
*/

void Sala::erase(App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py)
{
	celdas.erase(px, py);
}

/**
* Devuelve un vector con punteros a las celdas representables.
*/

std::vector<const App_Graficos::Representable *> Sala::obtener_vector_celdas_representables() const
{
	struct obtener
	{
		std::vector<const App_Graficos::Representable *> r;
		void operator()(const Celda& c) {r.push_back(&c);}
	}obt;

	celdas.aplicar(obt);
	return obt.r;
}

void Sala::insertar_entrada(const Entrada& e)
{
	//TODO: Comprobar que no existe una entrada para la misma posición.
	//TODO: Lanzar excepción si ya existe.
	entradas.push_back(e);

	direcciones_entradas=direcciones_entradas | e.acc_posicion();
}

const Entrada& Sala::obtener_entrada_posicion(App_Definiciones::direcciones p)
{
	for(const auto& e : entradas)
	{
		if(e.acc_posicion()==p) return e;
	}
	throw std::logic_error("No hay entrada en la posición establecida");
}
