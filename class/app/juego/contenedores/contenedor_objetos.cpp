#include "contenedor_objetos.h"

using namespace App_Juego_Contenedores;

Contenedor_objetos::Contenedor_objetos()
	:
	direcciones_entradas(App_Definiciones::direcciones::nada),
	posicion_inicial(nullptr),
	salida(nullptr)
{

}

/**
* @param Entrada e
* @throws std::logic_error cuando existe una entrada en la posición.
* Inserta una entrada en el vector de entradas. Se comprueba si se ha
* intentado insertar una entrada para la misma posición antes, lo que
* lanzaría la excepción.
*/

void Contenedor_objetos::insertar_entrada(const App_Juego_ObjetoJuego::Entrada& e)
{
	using namespace App_Definiciones;

	if( (direcciones_entradas & e.acc_posicion() ) != direcciones::nada)
	{
		throw std::logic_error("Ya existe una entrada en la posición indicada");
	}
	
	entradas.push_back(e);
	direcciones_entradas=direcciones_entradas | e.acc_posicion();
}

void Contenedor_objetos::sumar_variante(const Contenedor_objetos& o)
{
	for(auto& ob : o.objetos_juego) objetos_juego.push_back(ob);
	for(auto& ob : o.bonus) bonus.push_back(ob);
	for(auto& ob : o.con_turno) con_turno.push_back(ob);
	for(auto& ob : o.disparables) disparables.push_back(ob);
	for(auto& ob : o.disparadores) disparadores.push_back(ob);
	for(auto& ob : o.representables) representables.push_back(ob);
	for(auto& ob : o.colisionables) colisionables.push_back(ob);
	for(auto& ob : o.sonoros) sonoros.push_back(ob);
	for(auto& ob : o.generadores_objetos_juego) generadores_objetos_juego.push_back(ob);
}


/**
* @return size_t : indicando el número de elementos eliminados.
*
* Recorre el vector de objetos juego elíminando de forma definitiva todos los
* actores que puedan estar para borrar.
* Todos los objetos_juego no son borrables, de modo que necesitaremos algún
* tipo de visitante que extraiga lo que necesitamos. Como no podemos sacar
* un vector de borrables y eliminarlos del vector de objetos_juego usamos un 
* visitante que extrae la faceta deseada.
*/

size_t Contenedor_objetos::limpiar_para_borrar()
{
	size_t	res=ayudante_borrar(objetos_juego);

	/**	
	* Si hay algo para borrar buscaremos en el resto de vectores...
	*/

	if(res)
	{
		//TODO: Buen sitio para aprender a usar std::function y quitar las especializaciones...
		ayudante_borrar(bonus);
		ayudante_borrar(con_turno);
		ayudante_borrar(disparables);
		ayudante_borrar(disparadores);
		ayudante_borrar(colisionables);
		ayudante_borrar(generadores_objetos_juego);

		//Y las especializaciones malvadas.
		{
		auto 	ini=std::begin(representables);
		while(ini < std::end(representables))
		{
			if(ini->get()->es_representable_borrar()) ini=representables.erase(ini);
			else ++ini;
		}
		}

		{
		auto 	ini=std::begin(sonoros);
		while(ini < std::end(sonoros))
		{
			if(ini->get()->es_sonoro_borrar()) ini=sonoros.erase(ini);
			else ++ini;
		}
		}
	}

	return res;
}

void Contenedor_objetos::fusionar_con(Contenedor_objetos& c)
{
	std::move(std::begin(c.objetos_juego), std::end(c.objetos_juego), std::back_inserter(objetos_juego));
	std::move(std::begin(c.bonus), std::end(c.bonus), std::back_inserter(bonus));
	std::move(std::begin(c.con_turno), std::end(c.con_turno), std::back_inserter(con_turno));
	std::move(std::begin(c.disparables), std::end(c.disparables), std::back_inserter(disparables));
	std::move(std::begin(c.disparadores), std::end(c.disparadores), std::back_inserter(disparadores));
	std::move(std::begin(c.colisionables), std::end(c.colisionables), std::back_inserter(colisionables));
	std::move(std::begin(c.generadores_objetos_juego), std::end(c.generadores_objetos_juego), std::back_inserter(generadores_objetos_juego));
	std::move(std::begin(c.representables), std::end(c.representables), std::back_inserter(representables));
	std::move(std::begin(c.sonoros), std::end(c.sonoros), std::back_inserter(sonoros));
}
