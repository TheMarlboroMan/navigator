#include "traductor_mapas.h"
#include <generador_numeros.h>

#include "parser_salas.h"
#include "../juego/objetos_juego/bonus_tiempo.h"
#include "../juego/objetos_juego/bonus_salud.h"
#include "../juego/objetos_juego/enemigo_basico.h"

using namespace App_Generador;
using namespace App_Niveles;
using namespace App_Definiciones;
using namespace Herramientas_proyecto;

App_Niveles::Mapa Traductor_mapas::traducir_mapa(const std::vector<Proto_sala>& p, App_RepositorioSalas::Repositorio_salas& repo, const App_Lectores::Info_obstaculos_genericos& iog)
{
	//TODO: Teh suckage...
	t_dim w=0, h=0;

	for(const auto& ps : p)
	{
		int x=ps.acc_x();
		int y=ps.acc_y();

		if(x > w) w=x;
		if(y > h) h=y;
	}

	//Of course, convertimos de indice 0.
	++w;++h;
	LOG<<"Creando mapa de "<<w<<"x"<<h<<std::endl;
	Mapa resultado(w, h);

	//Indicar al nivel cuál es la celda inicial, que es la primera que tenemos.
	resultado.establecer_coordenadas_sala_inicial(p[0].acc_x(), p[0].acc_y());

	LOG<<"Iniciando parseo de salas"<<std::endl;

	//Generar las salas de turno.
	for(const Proto_sala& ps : p)
	{
		parsear_sala(ps, resultado, repo, iog);
	}

	return resultado;
}

App_Niveles::Mapa Traductor_mapas::traducir_mapa_test(int tipo, int nivel, int variante, App_RepositorioSalas::Repositorio_salas& repo, const App_Lectores::Info_obstaculos_genericos& iog)
{
	try
	{		
		LOG<<"Creando mapa test para tipo:"<<tipo<<" nivel:"<<nivel<<" variante:"<<variante<<std::endl;
		Mapa resultado(1, 1);
		resultado.establecer_coordenadas_sala_inicial(0, 0);

		//Componer nombre de sala a probar...
		std::stringstream ss;
		ss<<"data/salas/"<<tipo<<"/"<<tipo<<"_"<<std::setw(3)<<std::setfill('0')<<nivel<<".dat";

		Parser_salas parser;
		parser.parsear_fichero(ss.str(), iog);

		if((size_t)variante >= parser.cuenta_contenedores())
		{
			throw std::runtime_error("La variante de sala es inválida");
		}

		parser.generar_variante_sala(variante, Parser_salas::tipo_sala::inicio);
		parser.acc_sala().modificar_posicion(0, 0);

		resultado.insertar_sala(0, 0, parser.acc_sala());
		return resultado;
	}
	catch(Herramientas_proyecto::Matriz_2d_excepcion& e)
	{
		LOG<<"Error al insertar la sala generada..."<<std::endl;
		throw std::runtime_error("Error al insertar sala de test...");
	}

}

void Traductor_mapas::parsear_sala(const Proto_sala& ps, App_Niveles::Mapa& resultado, App_RepositorioSalas::Repositorio_salas& repo, const App_Lectores::Info_obstaculos_genericos& iog)
{
	Parser_salas parser;
	parser.parsear_fichero(repo.obtener_ruta_sala(ps.acc_salidas()), iog);

	/**
	* La sala hay que "compilarla" una vez parseado el fichero. Básicamente
	* hay que generar una de las variantes posibles e indicar si es el fin
	* o el principio para eliminar entidades especiales.
	*/

	Herramientas_proyecto::Generador_int G(1, parser.cuenta_contenedores()-1);

	Parser_salas::tipo_sala t=Parser_salas::tipo_sala::normal;
	if(ps.es_inicio()) t=Parser_salas::tipo_sala::inicio;
	else if(ps.es_fin()) t=Parser_salas::tipo_sala::fin;

	parser.generar_variante_sala(G(), t);

	try
	{
		parser.acc_sala().modificar_posicion(ps.acc_x(), ps.acc_y());
		resultado.insertar_sala(ps.acc_x(), ps.acc_y(), parser.acc_sala());
	}
	catch(Matriz_2d_excepcion& e)
	{
		LOG<<"ERROR AL INSERTAR SALA "<<e.x<<","<<e.y<<" : "<<e.what()<<std::endl;
		throw e;
	}
}
