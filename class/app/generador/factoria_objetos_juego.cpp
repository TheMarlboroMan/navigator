#include "factoria_objetos_juego.h"

using namespace App_Generador;
using namespace App_Juego_ObjetoJuego;
using namespace App_Interfaces;
using namespace DLibH;

void Factoria_objetos_juego::interpretar_linea(const std::string& linea)
{
	const auto params=Herramientas::explotar(linea, ',');
	const int tipo=toi(params[0]);

	try
	{
		switch(tipo)
		{
			case bonus_tiempo: 	interpretar_como_bonus_tiempo(params); break;
			case bonus_salud:	interpretar_como_bonus_salud(params); break;
			case enemigo_basico:	interpretar_como_enemigo_basico(params); break;
			case entrada:		interpretar_como_entrada(params); break;
			case posicion_inicial:	interpretar_como_posicion_inicial(params); break;
			default:
				LOG<<"No se ha interpretado la línea "<<linea<<" por ser de tipo ["<<tipo<<"] desconocido."<<std::endl;
			break;
		}
	}
	catch(Factoria_objetos_juego_excepcion& e)
	{
		LOG<<"ERROR Al interpretar línea como "<<e.tipo<<". Se esperan ["<<e.longitud_esperada<<"] parámetros, se reciben ["<<e.longitud_parametros<<"] <"<<linea<<">"<<std::endl;
	}
}


void Factoria_objetos_juego::interpretar_como_bonus_tiempo(const std::vector<std::string>& params)
{
	if(params.size() != lp_bonus_tiempo)
	{
		throw Factoria_objetos_juego_excepcion(params.size(), lp_bonus_tiempo, "Bonus tiempo");
	}
	else
	{
		const int x=toi(params[1]);
		const int y=toi(params[2]);
		const int cantidad=toi(params[3]);
	
		std::shared_ptr<Bonus_tiempo> ob(new Bonus_tiempo(x, y, cantidad));

		contenedor.objetos_juego.push_back(ob);
		contenedor.representables.push_back( std::shared_ptr<Representable_I>(ob, static_cast<Representable_I*>(ob.get())));
		contenedor.bonus.push_back(std::shared_ptr<Bonus_I>(ob, static_cast<Bonus_I*>(ob.get())));
	}
}

void Factoria_objetos_juego::interpretar_como_bonus_salud(const std::vector<std::string>& params)
{
	if(params.size() != lp_bonus_tiempo)
	{
		throw Factoria_objetos_juego_excepcion(params.size(), lp_bonus_salud, "Bonus salud");
	}
	else
	{
		const int x=toi(params[1]);
		const int y=toi(params[2]);
		const int cantidad=toi(params[3]);
		std::shared_ptr<Bonus_salud> ob(new Bonus_salud(x, y, cantidad));

		contenedor.objetos_juego.push_back(ob);
		contenedor.representables.push_back(std::shared_ptr<Representable_I>(ob, static_cast<Representable_I*>(ob.get())));
		contenedor.bonus.push_back(std::shared_ptr<Bonus_I>(ob, static_cast<Bonus_I*>(ob.get())));
	}
}

void Factoria_objetos_juego::interpretar_como_enemigo_basico(const std::vector<std::string>& params)
{
	if(params.size() != lp_enemigo_basico)
	{
		throw Factoria_objetos_juego_excepcion(params.size(), lp_enemigo_basico, "Enemigo básico");
	}
	else
	{
		const int x=toi(params[1]);
		const int y=toi(params[2]);
		const int salud=toi(params[3]);
		std::shared_ptr<Enemigo_basico> ob(new Enemigo_basico(x, y, salud));

		contenedor.objetos_juego.push_back(ob);
		contenedor.colisionables.push_back(std::shared_ptr<Colisionable_I>(ob, static_cast<Colisionable_I*>(ob.get())));
		contenedor.representables.push_back(std::shared_ptr<Representable_I>(ob, static_cast<Representable_I*>(ob.get())));
		contenedor.con_turno.push_back(std::shared_ptr<Con_turno_I>(ob, static_cast<Con_turno_I*>(ob.get())));
		contenedor.disparables.push_back(std::shared_ptr<Disparable_I>(ob, static_cast<Disparable_I*>(ob.get())));
		contenedor.disparadores.push_back(std::shared_ptr<Disparador_I>(ob, static_cast<Disparador_I*>(ob.get())));
	}
}

void Factoria_objetos_juego::interpretar_como_entrada(const std::vector<std::string>& params)
{
	if(params.size() != lp_entrada)
	{
		throw Factoria_objetos_juego_excepcion(params.size(), lp_entrada, "Entrada");
	}
	else
	{
		const int x=toi(params[1]);
		const int y=toi(params[2]);
		const App_Definiciones::direcciones pos=App_Definiciones::convertir_en_direccion(toi(params[3]));
		Entrada e(pos, x, y);
		contenedor.insertar_entrada(e);
	}
}

void Factoria_objetos_juego::interpretar_como_posicion_inicial(const std::vector<std::string>& params)
{
	if(params.size() != lp_posicion_inicial)
	{
		throw Factoria_objetos_juego_excepcion(params.size(), lp_posicion_inicial, "Posición inicial");
	}
	else
	{
		const int x=toi(params[1]);
		const int y=toi(params[2]);

		contenedor.posicion_inicial=Posicion_inicial(x, y);
	}
}
