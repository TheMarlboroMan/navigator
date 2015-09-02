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

//TODO: Considerar si esto es lo mismo que "fusionar con".

void Contenedor_objetos::sumar_variante(const Contenedor_objetos& o)
{
	std::move(std::begin(o.objetos_juego), std::end(o.objetos_juego), std::back_inserter(objetos_juego));
	std::move(std::begin(o.con_turno), std::end(o.con_turno), std::back_inserter(con_turno));
	std::move(std::begin(o.disparables), std::end(o.disparables), std::back_inserter(disparables));
	std::move(std::begin(o.solidos), std::end(o.solidos), std::back_inserter(solidos));
	std::move(std::begin(o.representables), std::end(o.representables), std::back_inserter(representables));
	std::move(std::begin(o.sonoros), std::end(o.sonoros), std::back_inserter(sonoros));
	std::move(std::begin(o.generadores_objetos_juego), std::end(o.generadores_objetos_juego), std::back_inserter(generadores_objetos_juego));
	std::move(std::begin(o.efectos_colision), std::end(o.efectos_colision), std::back_inserter(efectos_colision));
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
		ayudante_borrar(con_turno);
		ayudante_borrar(disparables);
		ayudante_borrar(efectos_colision);
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

		//TODO: Of course, borrar los sólidos simplemente no compila ¬¬....
		//ayudante_borrar(solidos);
	}

	return res;
}

void Contenedor_objetos::fusionar_con(Contenedor_objetos& c)
{
	std::move(std::begin(c.objetos_juego), std::end(c.objetos_juego), std::back_inserter(objetos_juego));
	std::move(std::begin(c.con_turno), std::end(c.con_turno), std::back_inserter(con_turno));
	std::move(std::begin(c.disparables), std::end(c.disparables), std::back_inserter(disparables));
	std::move(std::begin(c.solidos), std::end(c.solidos), std::back_inserter(solidos));
	std::move(std::begin(c.generadores_objetos_juego), std::end(c.generadores_objetos_juego), std::back_inserter(generadores_objetos_juego));
	std::move(std::begin(c.representables), std::end(c.representables), std::back_inserter(representables));
	std::move(std::begin(c.sonoros), std::end(c.sonoros), std::back_inserter(sonoros));
	std::move(std::begin(c.efectos_colision), std::end(c.efectos_colision), std::back_inserter(efectos_colision));
}

//TODO: Quizás podamos especializar "back_inserter".

std::vector<App_Interfaces::Generador_objetos_juego_I *> Contenedor_objetos::recolectar_generadores_objetos_juego()
{
	std::vector<App_Interfaces::Generador_objetos_juego_I *> v;
	for(auto& o : generadores_objetos_juego) v.push_back(o.get());
	return v;
}

std::vector<App_Interfaces::Con_turno_I *> Contenedor_objetos::recolectar_con_turno()
{
	std::vector<App_Interfaces::Con_turno_I *> v;
	for(auto& o : con_turno) v.push_back(o.get());
	return v;
}

std::vector<App_Interfaces::Disparable_I *> Contenedor_objetos::recolectar_disparables()
{
	std::vector<App_Interfaces::Disparable_I *> v;
	for(auto& o : disparables) v.push_back(o.get());
	return v;
}

std::vector<App_Interfaces::Efecto_colision_I *> Contenedor_objetos::recolectar_efectos_colision()
{
	std::vector<App_Interfaces::Efecto_colision_I *> v;
	for(auto& o : efectos_colision) v.push_back(o.get());
	return v;
}

std::vector<App_Interfaces::Espaciable *> Contenedor_objetos::recolectar_solidos()
{
	std::vector<App_Interfaces::Espaciable *> v;
	for(auto& o : solidos) v.push_back(o.get());
	return v;
}

///////////////

std::vector<const App_Interfaces::Generador_objetos_juego_I *> Contenedor_objetos::recolectar_generadores_objetos_juego() const 
{
	std::vector<const App_Interfaces::Generador_objetos_juego_I *> v;
	for(const auto& o : generadores_objetos_juego) v.push_back(o.get());
	return v;
}

std::vector<const App_Interfaces::Con_turno_I *> Contenedor_objetos::recolectar_con_turno() const 
{
	std::vector<const App_Interfaces::Con_turno_I *> v;
	for(const auto& o : con_turno) v.push_back(o.get());
	return v;
}

std::vector<const App_Interfaces::Disparable_I *> Contenedor_objetos::recolectar_disparables() const 
{
	std::vector<const App_Interfaces::Disparable_I *> v;
	for(const auto& o : disparables) v.push_back(o.get());
	return v;
}

std::vector<const App_Interfaces::Efecto_colision_I *> Contenedor_objetos::recolectar_efectos_colision() const 
{
	std::vector<const App_Interfaces::Efecto_colision_I *> v;
	for(const auto& o : efectos_colision) v.push_back(o.get());
	return v;
}

std::vector<const App_Interfaces::Espaciable *> Contenedor_objetos::recolectar_solidos() const
{
	std::vector<const App_Interfaces::Espaciable *> v;
	for(const auto& o : solidos) v.push_back(o.get());
	return v;
}

/*
void Contenedor_objetos::recolectar_generador_objetos_juego(std::vector<App_Interfaces::Generador_objetos_juego_I *>& v)
{
	for(auto& o : generadores_objetos_juego) v.push_back(o.get());
}
*/
