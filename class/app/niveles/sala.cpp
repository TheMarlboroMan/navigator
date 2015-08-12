#include "sala.h"

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

std::vector<const App_Interfaces::Representable_I *> Sala::obtener_vector_representables() const
{
	using namespace App_Interfaces;

	typedef std::vector<const App_Interfaces::Representable_I *> t_res;
	t_res resultado;

	struct obtener
	{		
		obtener(t_res& res):r(res) {}
		t_res& r;
		void operator()(const Celda& c) {r.push_back(&c);}
	}obt(resultado);

	//Recolectar las celdas.
	celdas.aplicar(obt);

	//Recolectar los objetos juego.
	for(auto& o : objetos.representables) resultado.push_back(o.get());

	return resultado;
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
	if( (direcciones_entradas & e.acc_posicion() ) != direcciones::nada)
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
	size_t	res=ayudante_borrar(objetos.objetos_juego);

	/**	
	* Si hay algo para borrar buscaremos en el resto de vectores...
	*/

	if(res)
	{
		ayudante_borrar(objetos.bonus);
		ayudante_borrar(objetos.con_turno);
		ayudante_borrar(objetos.disparables);
		ayudante_borrar(objetos.disparadores);
		ayudante_borrar(objetos.colisionables);

		//Y la especialización malvada.
		auto 	ini=std::begin(objetos.representables),
			fin=std::end(objetos.representables);
	
		while(ini < fin)
		{
			if(ini->get()->es_representable_borrar())
			{
				ini=objetos.representables.erase(ini);
				fin=std::end(objetos.representables);
			}
			else
			{
				++ini;
			}
		}
	}

	return res;
}

void Sala::modificar_posicion_y_dimensiones(App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py, App_Definiciones::tipos::t_dim pw, App_Definiciones::tipos::t_dim ph)
{
	pos.x=px;
	pos.y=py;
	w=pw;
	h=ph;
	celdas=celdas.copiar_con_dimensiones(w, h);
}
