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
	:estado(t_estados::nada),
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

	//TODO: No hay información de salidas / entradas, pasarlas a "objetos juego" 
	//o algo así.

			if(interpretar_estado(linea))
			{
				switch(estado)
				{
					case t_estados::nada: 
					case t_estados::estructura: 
					case t_estados::info: 
					case t_estados::logica: 

					break;
					case t_estados::rejilla: interpretar_linea_como_rejilla(linea); break;
					case t_estados::celdas: interpretar_linea_como_celdas(linea); break;
					case t_estados::objetos: interpretar_linea_como_objeto(linea, factoria); break;

					//Poblar la sala. La factoría queda inútil tras esto.
					case t_estados::fin: 
						sala.implantar_objetos_juego(factoria.movible_contenedor_objetos_juego()); 
					break;
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
	else if(linea==TIPO_CELDAS) estado=t_estados::celdas;
	else if(linea==TIPO_LOGICA) estado=t_estados::logica;
	else if(linea==TIPO_OBJETOS) estado=t_estados::objetos;
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
	//TODO: Validar longitud de la información siempre.
	std::vector<std::string> valores=Herramientas::explotar(linea, ',');
	const auto w=toi(valores[0]), h=toi(valores[1]);
	sala.modificar_dimensiones(w, h);
}

void Parser_salas::interpretar_linea_como_celdas(const std::string& linea)
{
	//TODO: Validar longitud de la información siempre.

	std::vector<std::string> valores=Herramientas::explotar(linea, ' ');
	for(const auto& v : valores)
	{
		const auto& partes=Herramientas::explotar(v, ',');
		const int x=toi(partes[0]), y=toi(partes[1])/*, tipo=toi(partes[2])*/;
		sala.insertar_celda(x, y, App_Niveles::Celda::tipo_celda::solida);
	}
}

void Parser_salas::interpretar_linea_como_objeto(const std::string& linea, Factoria_objetos_juego& factoria)
{
	factoria.interpretar_linea(linea);
}
