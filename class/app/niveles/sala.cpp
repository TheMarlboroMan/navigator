#include "sala.h"
#include "../visitantes/visitante_objeto_juego.h"

//Incluir los diversos tipos de objetos de mapa...
#include "../juego/objetos_juego/bonus_tiempo.h"
#include "../juego/objetos_juego/bonus_salud.h"


using namespace App_Niveles;
using namespace HerramientasProyecto;
using namespace App_Definiciones;

/**
* @param t_dim pw 
* @param t_dim ph
* @param t_dim px
* @param t_dim py
*/

Sala::Sala(tipos::t_dim pw, tipos::t_dim ph, tipos::t_dim px, tipos::t_dim py)
	:pos(px, py), w(pw), h(ph), celdas(pw, ph),
	direcciones_entradas(App_Definiciones::direcciones::nada)
{

}

/**
* @param t_dim x
* @param t_dim y
* @param tipo_celda t
* @throw Matriz_2d_excepcion_item_existe cuando la celda está ocupada.
*/

void Sala::insertar_celda(App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py, Celda::tipo_celda pt)
{
	celdas(px, py, Celda(px, py, pt));
}

/**
* @param t_dim x
* @param t_dim_y
* @throw Matriz_2d_excepcion_item_invalido cuando no existe la celda.
*/

void Sala::erase(App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py)
{
	celdas.erase(px, py);
}

/**
* @return std::vector<const Representable *>
* Devuelve un vector con punteros a los objetos representables que contiene representables.
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
		virtual void visitar(const App_Juego_ObjetoJuego::Bonus_salud& o) {v.push_back(&o);}
	}v(obt.r);
	
	procesar_visitante_objetos_juego_const(v);

	return obt.r;
}

/**
* @param Entrada e
* @throws std::logic_error cuando existe una entrada en la posición.
* Inserta una entrada en el vector de entradas. Se comprueba si se ha
* intentado insertar una entrada para la misma posición antes, lo que
* lanzaría la excepción.
*/

void Sala::insertar_entrada(const Entrada& e)
{
	if(direcciones_entradas & e.acc_posicion())
	{
		throw std::logic_error("Ya existe una entrada en la posición indicada");
	}
	
	entradas.push_back(e);
	direcciones_entradas=direcciones_entradas | e.acc_posicion();
}

/**
* @return Entrada
* @throw std::logic_error cuando no hay entrada en esa posición.
*/

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
* Todos los objetos_juego no son borrables, de modo que necesitaremos algún
* tipo de visitante que extraiga lo que necesitamos. Como no podemos sacar
* un vector de borrables y eliminarlos del vector de objetos_juego usamos un 
* visitante que extrae la faceta deseada.
*/

size_t Sala::limpiar_objetos_juego_para_borrar()
{
	size_t	res=0;

	auto 	ini=std::begin(objetos_juego),
		fin=std::end(objetos_juego);

	//Visitante específico para sacar la faceta "borrable" de los objetos juego.
	struct Visitante_faceta_borrable:public App_Visitantes::Visitante_objeto_juego
	{
		bool borrar;
		Visitante_faceta_borrable():borrar(false){}
		virtual void visitar(App_Juego_ObjetoJuego::Bonus_tiempo& o) {borrar=o.es_borrar();}
		virtual void visitar(App_Juego_ObjetoJuego::Bonus_salud& o) {borrar=o.es_borrar();}
	}v;

	while(ini < fin)
	{
		(*ini)->recibir_visitante(v);
		if(v.borrar)
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
