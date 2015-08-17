#include "traductor_mapas.h"
#include "../../herramientas_proyecto/generador_numeros.h"

#include "parser_salas.h"
#include "../juego/objetos_juego/bonus_tiempo.h"
#include "../juego/objetos_juego/bonus_salud.h"
#include "../juego/objetos_juego/enemigo_basico.h"

using namespace App_Generador;
using namespace App_Niveles;
using namespace App_Definiciones;
using namespace HerramientasProyecto;

App_Niveles::Mapa Traductor_mapas::traducir_mapa(const std::vector<Proto_sala>& p, App_RepositorioSalas::Repositorio_salas& repo)
{
	//TODO: Teh suckage...
	t_dim w=0, h=0;

	for(const auto& ps : p)
	{
		unsigned int x=ps.acc_x();
		unsigned int y=ps.acc_y();

		if(x > w) w=x;
		if(y > h) h=y;
	}

	//Of course, convertimos de indice 0.
	++w;++h;
	Mapa resultado(w, h);

	//Indicar al nivel cuál es la celda inicial, que es la primera que tenemos.
	resultado.establecer_coordenadas_sala_inicial(p[0].acc_x(), p[0].acc_y());

	LOG<<"Iniciando parseo de salas"<<std::endl;

	//Generar las salas de turno.
	for(const Proto_sala& ps : p)
	{
		parsear_sala(ps, resultado, repo);
	}

	return resultado;
}

void Traductor_mapas::parsear_sala(const Proto_sala& ps, App_Niveles::Mapa& resultado, App_RepositorioSalas::Repositorio_salas& repo)
{
	Parser_salas parser;

	//TODO: Faltan las excepciones que esto puede tirar, que no son pocas.

	parser.parsear_fichero(repo.obtener_ruta_sala(ps.acc_salidas()));
//	parser.parsear_fichero("data/salas/1/1_001.dat");

	/**
	* La sala hay que "compilarla" una vez parseado el fichero. Básicamente
	* hay que generar una de las variantes posibles e indicar si es el fin
	* o el principio para eliminar entidades especiales.
	*/

	HerramientasProyecto::Generador_int G(1, parser.cuenta_contenedores()-1);

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
		//TODO: No no no... ¿Qué hacemos aquí?.
		//std::cout<<"ERROR AL INSERTAR SALA "<<e.x<<","<<e.y<<" : PARA "<<w<<"x"<<h<<" : "<<e.what()<<std::endl;
	}
}
