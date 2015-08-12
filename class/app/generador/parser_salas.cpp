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

void Parser_salas::parsear_fichero(const std::string& ruta, App_Definiciones::tipos::t_dim pos_x, App_Definiciones::tipos::t_dim pos_y)
{
	DLibH::Lector_txt L(ruta, '#');

	if(!L)
	{
		LOG<<"ERROR: Imposible localizar nivel en fichero "<<ruta<<std::endl;
	}
	else
	{	
		std::string linea;

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
					case t_estados::rejilla: interpretar_linea_como_rejilla(linea, pos_x, pos_y); break;
					case t_estados::celdas: interpretar_linea_como_celdas(linea); break;
					case t_estados::objetos: interpretar_linea_como_objeto(linea); break;
					case t_estados::fin:
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
	else if(linea==TIPO_FIN_ESTRUCTURA) estado=t_estados::fin;
	else
	{
		return true;
	}

	return false;
}

void Parser_salas::interpretar_linea_como_rejilla(const std::string& linea, App_Definiciones::tipos::t_dim pos_x, App_Definiciones::tipos::t_dim pos_y)
{
	//TODO: Validar longitud de la información siempre.

	std::vector<std::string> valores=Herramientas::explotar(linea, ',');
	sala.modificar_posicion_y_dimensiones(pos_x, pos_y, toi(valores[0]), toi(valores[1]));
}

void Parser_salas::interpretar_linea_como_celdas(const std::string& linea)
{
	//TODO: Validar longitud de la información siempre.

	std::vector<std::string> valores=Herramientas::explotar(linea, ' ');
	for(const auto& v : valores)
	{
		const auto& partes=Herramientas::explotar(v, ',');
		int x=toi(partes[0]), y=toi(partes[1])/*, tipo=toi(partes[2])*/;
		sala.insertar_celda(x, y, App_Niveles::Celda::tipo_celda::solida);
	}
}

void Parser_salas::interpretar_linea_como_objeto(const std::string& linea)
{
	//TODO: Validar longitud de la información siempre.

	//TODO: Generar una factoría para esto...

/*
	std::vector<std::string> partes=Herramientas::explotar(linea, ',');
	int tipo=toi(partes[0]), x=toi(partes[1]), y=toi(partes[2]);
	switch(tipo)
	{
		//Entrada
		case 1:
			//TODO: Comprobar que ya existe, etc etc...
			if(partes.size()!=6)
			{
				LOG<<"ERROR: Importando entrada, la linea "<<linea<<" no tiene 6 campos."<<std::endl;
			}
			else
			{
				unsigned int id=toi(partes[3]);
				unsigned int direccion=toi(partes[4]);
				unsigned int estado=toi(partes[5]);
				entradas.push_back(Entrada_nivel(x, y, id, direccion, estado));
			}
		break;

		case 2:
			if(partes.size()!=5)
			{
				LOG<<"ERROR: Importando entrada, la linea "<<linea<<" no tiene 5 campos."<<std::endl;
			}
			else
			{
				unsigned int nivel=toi(partes[3]);
				unsigned int id_entrada=toi(partes[4]);
				salidas.push_back(Salida_nivel(x, y, id_entrada, nivel));
			}
		break;
		
		default:
			LOG<<"ERROR: Importando conexiones, la linea "<<linea<<" no es reconocible."<<std::endl;
		break;
*/
}
