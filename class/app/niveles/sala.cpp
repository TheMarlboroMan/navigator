#include "sala.h"
#include "../visitantes/visitante_objeto_juego.h"

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

std::vector<const App_Graficos::Representable *> Sala::obtener_vector_representables() const
{
	struct obtener
	{
		std::vector<const App_Graficos::Representable *> r;
		void operator()(const Celda& c) {r.push_back(&c);}
	}obt;
	celdas.aplicar(obt);

	//Visitante específico para sacar la face "representable" de los objetos juego.
	struct Visitante_objeto_juego_vector_representable:public App_Visitantes::Visitante_objeto_juego_const
	{
		std::vector<const App_Graficos::Representable *>& v;
		Visitante_objeto_juego_vector_representable(std::vector<const App_Graficos::Representable *>& pv)
			:v(pv)
		{}
	
		virtual void visitar(const App_Juego_ObjetoJuego::Bonus_tiempo& o) {v.push_back(&o);}
	}v(obt.r);
	
	procesar_visitante_objetos_juego_const(v);

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

void Sala::insertar_objeto_juego(std::shared_ptr<App_Interfaces::Objeto_juego_I> obj)
{
	objetos_juego.push_back(obj);
}

/**
* @return size_t : indicando el número de elementos eliminados.
* Recorre el vector de objetos juego elíminando de forma definitiva todos los
* actores que puedan estar para borrar.
*/

size_t Sala::limpiar_objetos_juego_para_borrar()
{
	size_t	res=0;

	auto 	ini=std::begin(objetos_juego),
		fin=std::end(objetos_juego);

	while(ini < fin)
	{
		if( (*ini)->es_borrar() )
		{
			ini=objetos_juego.erase(ini);
			fin=std::end(objetos_juego);
			++res;
		}
		else
		{
			++ini;
		}		
	}

	return res;
}

void Sala::procesar_visitante_objetos_juego(App_Visitantes::Visitante_objeto_juego& v)
{
	for(auto& o : objetos_juego) o.get()->recibir_visitante(v);
}

void Sala::procesar_visitante_objetos_juego_const(App_Visitantes::Visitante_objeto_juego_const& v) const
{
	for(const auto& o : objetos_juego) o.get()->recibir_visitante(v);
}
