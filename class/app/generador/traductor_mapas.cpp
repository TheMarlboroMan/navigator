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
	tipos::t_dim w=0, h=0;

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
		//TODO: Ok, es hora de abrir los ficheros y parsearlos....
		parsear_sala(ps, resultado, repo);

/*
		//Crear sala.
		App_Definiciones::tipos::t_dim x=ps.acc_x(), y=ps.acc_y();
		//TODO: Esto debería ir en alguna constante, en algún lado.
		Sala sala=Sala(20, 10, x, y);

		//Excavar salidas de la sala.
		muros_sala(sala, ps.acc_salidas());

		//Incluir varios obstáculos en la sala.
		obstaculos_sala(sala);

		try
		{
			resultado.insertar_sala(x, y, sala);
		}
		catch(Matriz_2d_excepcion& e)
		{
			//TODO: No no no... ¿Qué hacemos aquí?.
			std::cout<<"ERROR AL INSERTAR SALA "<<e.x<<","<<e.y<<" : PARA "<<w<<"x"<<h<<" : "<<e.what()<<std::endl;
		}
*/
	}

	return resultado;
}

void Traductor_mapas::parsear_sala(const Proto_sala& ps, App_Niveles::Mapa& resultado, App_RepositorioSalas::Repositorio_salas& repo)
{
	Parser_salas parser;

	parser.parsear_fichero(repo.obtener_ruta_sala(ps.acc_salidas()));

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

void Traductor_mapas::muros_sala(Sala& sala, direcciones salidas)
{
	//Primero los muros...
	for(unsigned int x=0; x<sala.acc_w(); ++x)
	{
		sala.insertar_celda(x, 0, Celda::tipo_celda::solida);
		sala.insertar_celda(x, 9, Celda::tipo_celda::solida);
	}

	for(unsigned int y=1; y<sala.acc_h()-1; ++y)
	{
		sala.insertar_celda(0, y, Celda::tipo_celda::solida);
		sala.insertar_celda(19, y, Celda::tipo_celda::solida);
	}

	//Ahora colocar las salidas...

	auto ie=[&sala](direcciones pos, unsigned int x, unsigned int y)
	{
	//	sala.insertar_entrada( Entrada(pos, x*32, y*32));	
	};

	if( (salidas & direcciones::arriba) != direcciones::nada)
	{
		for(unsigned int i=9; i < 12; ++i) sala.erase(i, 0);
		ie(direcciones::arriba, 10, 0);
	}

	if( (salidas & direcciones::abajo) != direcciones::nada) 
	{
		unsigned int y=sala.acc_h()-1;
		for(unsigned int i=9; i < 12; ++i) sala.erase(i, y);
		ie(direcciones::abajo, 10, y);
	}

	if( (salidas & direcciones::izquierda) != direcciones::nada)
	{
		for(unsigned int i=5; i < 8; ++i) sala.erase(0, i);
		ie(direcciones::izquierda, 0, 6);
	}

	if( (salidas & direcciones::derecha) != direcciones::nada)
	{
		unsigned int x=sala.acc_w()-1;
		for(unsigned int i=5; i < 8; ++i) sala.erase(x, i);
		ie(direcciones::derecha, x, 6);
	}
}

void Traductor_mapas::obstaculos_sala(Sala& sala)
{
	using namespace HerramientasProyecto;
	using namespace App_Juego_ObjetoJuego;

	//Generar la cantidad de obstáculos...
	Generador_int GEN(0, 20);
	int c=GEN();

	Generador_int GX(1, 18);
	Generador_int GY(1, 8);

	while(c)
	{
		try
		{
			sala.insertar_celda(GX(), GY(), Celda::tipo_celda::solida);
			--c;
		}
		catch(Matriz_2d_excepcion_item_existe e)
		{
			//Nada, simplemente no decrementamos el contador.
		}
	}
/*
	auto& contenedor=sala.acc_contenedor_objetos();

	using namespace App_Interfaces;

	//De forma super cutre, vamos a volcar unos bonus.

	//TODO: Buscar otra forma, una factoría o algo.

	std::shared_ptr<Bonus_tiempo> bt(new Bonus_tiempo(GX()*App_Definiciones::tipos::DIM_CELDA, GY()*App_Definiciones::tipos::DIM_CELDA));
	contenedor.objetos_juego.push_back(bt);
	contenedor.representables.push_back( std::shared_ptr<Representable_I>(bt, static_cast<Representable_I*>(bt.get())));
	contenedor.bonus.push_back(std::shared_ptr<Bonus_I>(bt, static_cast<Bonus_I*>(bt.get())));

	std::shared_ptr<Bonus_salud> bs(new Bonus_salud(GX()*App_Definiciones::tipos::DIM_CELDA, GY()*App_Definiciones::tipos::DIM_CELDA));
	contenedor.objetos_juego.push_back(bs);
	contenedor.representables.push_back(std::shared_ptr<Representable_I>(bs, static_cast<Representable_I*>(bs.get())));
	contenedor.bonus.push_back(std::shared_ptr<Bonus_I>(bs, static_cast<Bonus_I*>(bs.get())));

	std::shared_ptr<Enemigo_basico> enem(new Enemigo_basico(GX()*App_Definiciones::tipos::DIM_CELDA, GY()*App_Definiciones::tipos::DIM_CELDA));
	contenedor.objetos_juego.push_back(enem);
	contenedor.colisionables.push_back(std::shared_ptr<Colisionable_I>(enem, static_cast<Colisionable_I*>(enem.get())));
	contenedor.representables.push_back(std::shared_ptr<Representable_I>(enem, static_cast<Representable_I*>(enem.get())));
	contenedor.con_turno.push_back(std::shared_ptr<Con_turno_I>(enem, static_cast<Con_turno_I*>(enem.get())));
	contenedor.disparables.push_back(std::shared_ptr<Disparable_I>(enem, static_cast<Disparable_I*>(enem.get())));
	contenedor.disparadores.push_back(std::shared_ptr<Disparador_I>(enem, static_cast<Disparador_I*>(enem.get())));
*/
}
