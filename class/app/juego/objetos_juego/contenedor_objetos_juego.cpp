#include "contenedor_objetos_juego.h"

using namespace App_Juego_ObjetoJuego;

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

void Contenedor_objetos::insertar_entrada(const Entrada& e)
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
		ayudante_borrar(bonus);
		ayudante_borrar(con_turno);
		ayudante_borrar(disparables);
		ayudante_borrar(disparadores);
		ayudante_borrar(colisionables);

		//Y la especialización malvada.
		auto 	ini=std::begin(representables),
			fin=std::end(representables);
	
		while(ini < fin)
		{
			if(ini->get()->es_representable_borrar())
			{
				ini=representables.erase(ini);
				fin=std::end(representables);
			}
			else
			{
				++ini;
			}
		}
	}

	return res;
}
