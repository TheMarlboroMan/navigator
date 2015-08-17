#include "parser_salas.h"

using namespace App_Generador;

const std::string Parser_salas::TIPO_ESTRUCTURA="[ESTRUCTURA]";
const std::string Parser_salas::TIPO_FIN_ESTRUCTURA="[/ESTRUCTURA]";
const std::string Parser_salas::TIPO_INFO="[INFO]";
const std::string Parser_salas::TIPO_REJILLA="[REJILLA]";
const std::string Parser_salas::TIPO_CELDAS="[CELDAS]";
const std::string Parser_salas::TIPO_CAMARA="[CAMARA]";
const std::string Parser_salas::TIPO_LOGICA="[LOGICA]";
const std::string Parser_salas::TIPO_OBJETOS="[OBJETOS]";
		

Parser_salas::Parser_salas()
	:d_celdas(destino_celdas::nada), estado(t_estados::nada),
	sala(1,1,0,0)
{

}

void Parser_salas::parsear_fichero(const std::string& ruta)
{
	DLibH::Lector_txt L(ruta, '#');

	if(!L)
	{
		LOG<<"ERROR: Imposible localizar nivel en fichero "<<ruta<<std::endl;
	}
	else
	{	
		std::string linea;

		//La factoría contendrá los objetos de juego hasta que finalmente
		//se implanten en la sala.
		Factoria_objetos_juego factoria;

		while(true)
		{
			linea=L.leer_linea();
			if(!L) break;

			if(interpretar_estado(linea))
			{
				switch(estado)
				{
					case t_estados::nada: 
					case t_estados::estructura: 
					case t_estados::info: 
					case t_estados::logica: 
					case t_estados::fin: 
					break;
					case t_estados::rejilla: interpretar_linea_como_rejilla(linea); break;
					case t_estados::celdas: interpretar_linea_como_celdas(linea); break;
					case t_estados::objetos: interpretar_linea_como_objeto(linea, factoria); break;
				}
			}
		}
	}
}

bool Parser_salas::interpretar_estado(const std::string& linea)
{
	if(linea==TIPO_ESTRUCTURA) estado=t_estados::estructura;
	else if(linea==TIPO_INFO) estado=t_estados::info;
	else if(linea==TIPO_REJILLA) estado=t_estados::rejilla;
	else if(linea==TIPO_CELDAS) 
	{
		//Cada vez que encuentre una, aumentamos el destino.
		switch(d_celdas)
		{
			case destino_celdas::nada: 	d_celdas=destino_celdas::logica; break;
			case destino_celdas::logica: 	d_celdas=destino_celdas::decoracion; break;
			case destino_celdas::decoracion: throw std::runtime_error("Demasiadas secciones de celda en sala."); break;
		}

		estado=t_estados::celdas;
	}	
	else if(linea==TIPO_LOGICA) estado=t_estados::logica;
	else if(linea==TIPO_OBJETOS) 
	{
		//Por cada vez que se encuentre esta tag, añadimos un contenedor al final.
		contenedores.push_back(App_Juego_ObjetoJuego::Contenedor_objetos());
		estado=t_estados::objetos;
	}
	else if(linea==TIPO_FIN_ESTRUCTURA) 
	{
		estado=t_estados::fin;
		return true; //Hay que ejecutar una acción al cerrar la estructura.
	}
	else return true;
	return false;
}

void Parser_salas::interpretar_linea_como_rejilla(const std::string& linea)
{
	std::vector<std::string> valores=Herramientas::explotar(linea, ',');

	if(valores.size() < 2)
	{
		throw std::runtime_error("ERROR: Al interpretar línea como rejilla hay menos de 2 parámetros");
	}

	const auto w=toi(valores[0]), h=toi(valores[1]);
	sala.modificar_dimensiones(w, h);
}

void Parser_salas::interpretar_linea_como_celdas(const std::string& linea)
{
	std::vector<std::string> valores=Herramientas::explotar(linea, ' ');

	for(const auto& v : valores)
	{
		const auto& partes=Herramientas::explotar(v, ',');

		if(partes.size() != 3)
		{
			throw std::runtime_error("ERROR: Al interpretar línea "+v+" como celda hay debe haber 3 parámetros.");
		}

		const int x=toi(partes[0]), y=toi(partes[1])/*, tipo=toi(partes[2])*/;

		switch(d_celdas)
		{
			case destino_celdas::nada: break;
			case destino_celdas::logica: 	
				sala.insertar_celda(x, y, App_Niveles::Celda::tipo_celda::solida);
			break;
			case destino_celdas::decoracion: 
				sala.insertar_celda_decorativa(x, y, toi(partes[2]));
			break;
		}
	}
}

void Parser_salas::interpretar_linea_como_objeto(const std::string& linea, Factoria_objetos_juego& factoria)
{
	factoria.interpretar_linea(linea, contenedores.back());
}

/**
* Se comprueba que la sala se ha creado de acuerdo con las siguientes normas:
* - Tiene al menos el contenedor principal una variante.
* - El contenedor principal contiene inicio, fin y entradas.
* - Las variantes no tienen inicio, fin ni entradas.
*/

bool Parser_salas::comprobar_validez_sala() const
{	

	//TODO: Separar el contenedor principal del resto de contenedores. Está
	//ensuciando mucho el código.


	if(contenedores.size() <= 1) 
	{
		LOG<<"Se detecta que no hay variantes para la sala."<<std::endl;
		return false;
	}

	auto& primero=contenedores.front();

	if(primero.posicion_inicial == nullptr)
	{
		LOG<<"Se detecta que no hay posición inicial en contenedor principal."<<std::endl;
		return false;
	}
	else if(primero.salida == nullptr)
	{		
		LOG<<"Se detecta que no hay posición de salida en contenedor principal."<<std::endl;
		return false;
	}
	else if(!primero.entradas.size())
	{
		LOG<<"Se detecta que no hay entradas en contenedor principal."<<std::endl;
		return false;
	}
	
	auto it=contenedores.begin()+1;
	while(it < contenedores.end())
	{
		if(it->entradas.size())
		{
			LOG<<"Se detectan entradas en variación de sala."<<std::endl;
			return false;
		}

		if(it->posicion_inicial != nullptr)
		{
			LOG<<"Se detecta una posición inicial en variación de sala."<<std::endl;
			return false;
		}
	
		if(it->salida != nullptr)
		{		
			LOG<<"Se detecta una salida en variación de sala."<<std::endl;
			return false;
		}

		++it;
	}

	return true;
}

/**
* @param size_t v : La variante que vamos a usar empezando por 0.
* @param tipo_sala t : El tipo de sala, que indicará 
* Compone un nuevo contenedor a partir del contenedor[0] con las cosas comunes
* y los valores de la variante escogida. Ese contenedor luego se asigna a la
* sala.
*/ 

void Parser_salas::generar_variante_sala(size_t v, tipo_sala t)
{
	if(v==0) throw std::runtime_error("ERROR: Se intenta generar la variante 0");

	//Copia del contenedor original.
	auto c=contenedores.front();

	/**
	* Esto tiene su historia: si vamos a borrar la salida hay que tener
	* en cuenta que hay referencias a la misma en los contenedores de 
	* interfaces, luego hay que marcarlos para borrar, limpiar y después 
	* elimianr la referencia.
	*/

	auto eliminar_fin=[&c]()
	{
		c.salida->mut_borrar(true);
		c.limpiar_para_borrar();
		c.salida.reset();
	};

	switch(t)
	{
		case tipo_sala::normal:
			eliminar_fin();
			c.posicion_inicial.reset();
		break;
		case tipo_sala::inicio:
			eliminar_fin();
		break;
		case tipo_sala::fin: 
			c.posicion_inicial.reset();
		break;
	}

	//Finalmente, generar la variante e implantar. El +1 es porque el cero son las salidas y entradas.
	c.sumar_variante(contenedores[v]);

	sala.implantar_objetos_juego(std::move(c));
}
