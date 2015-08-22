#include "factoria_objetos_juego.h"

using namespace App_Generador;
using namespace App_Juego_ObjetoJuego;
using namespace App_Interfaces;
using namespace DLibH;


void Factoria_objetos_juego::interpretar_linea(const std::string& linea, App_Juego_ObjetoJuego::Contenedor_objetos& contenedor)
{
	const auto params=Herramientas::explotar(linea, ',');
	const int tipo=toi(params[0]);

	try
	{
		switch(tipo)
		{
			case bonus_tiempo: 	interpretar_como_bonus_tiempo(params, contenedor); break;
			case bonus_salud:	interpretar_como_bonus_salud(params, contenedor); break;
			case enemigo_basico:	interpretar_como_enemigo_basico(params, contenedor); break;
			case enemigo_rebote:	interpretar_como_enemigo_rebote(params, contenedor); break;
			case entrada:		interpretar_como_entrada(params, contenedor); break;
			case salida:		interpretar_como_salida(params, contenedor); break;
			case posicion_inicial:	interpretar_como_posicion_inicial(params, contenedor); break;
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


void Factoria_objetos_juego::interpretar_como_bonus_tiempo(const std::vector<std::string>& params, App_Juego_ObjetoJuego::Contenedor_objetos& contenedor)
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

void Factoria_objetos_juego::interpretar_como_bonus_salud(const std::vector<std::string>& params, App_Juego_ObjetoJuego::Contenedor_objetos& contenedor)
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

void Factoria_objetos_juego::interpretar_como_enemigo_basico(const std::vector<std::string>& params, App_Juego_ObjetoJuego::Contenedor_objetos& contenedor)
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
		contenedor.sonoros.push_back(std::shared_ptr<Sonoro_I>(ob, static_cast<Sonoro_I*>(ob.get())));
		contenedor.con_turno.push_back(std::shared_ptr<Con_turno_I>(ob, static_cast<Con_turno_I*>(ob.get())));
		contenedor.disparables.push_back(std::shared_ptr<Disparable_I>(ob, static_cast<Disparable_I*>(ob.get())));
		contenedor.disparadores.push_back(std::shared_ptr<Disparador_I>(ob, static_cast<Disparador_I*>(ob.get())));
	}
}

void Factoria_objetos_juego::interpretar_como_enemigo_rebote(const std::vector<std::string>& params, App_Juego_ObjetoJuego::Contenedor_objetos& contenedor)
{
	if(params.size() != lp_enemigo_rebote)
	{
		throw Factoria_objetos_juego_excepcion(params.size(), lp_enemigo_rebote, "Enemigo rebote");
	}
	else
	{
		using namespace App_Definiciones;

		const int x=toi(params[1]);
		const int y=toi(params[2]);
		const int velocidad=toi(params[3]);
		const int tr=toi(params[4]);
		const direcciones dir=convertir_en_direccion(toi(params[5]));

		Enemigo_rebote::tipos_rebote tipo_rebote=Enemigo_rebote::tipos_rebote::invertir;
		if(tr==1) tipo_rebote=Enemigo_rebote::tipos_rebote::derecha;
		else if(tr==2) tipo_rebote=Enemigo_rebote::tipos_rebote::izquierda;

		std::shared_ptr<Enemigo_rebote> ob(new Enemigo_rebote(x, y, velocidad, tipo_rebote, dir));

		contenedor.objetos_juego.push_back(ob);
		contenedor.colisionables.push_back(std::shared_ptr<Colisionable_I>(ob, static_cast<Colisionable_I*>(ob.get())));
		contenedor.representables.push_back(std::shared_ptr<Representable_I>(ob, static_cast<Representable_I*>(ob.get())));
		contenedor.con_turno.push_back(std::shared_ptr<Con_turno_I>(ob, static_cast<Con_turno_I*>(ob.get())));
		contenedor.disparables.push_back(std::shared_ptr<Disparable_I>(ob, static_cast<Disparable_I*>(ob.get())));
	}
}

void Factoria_objetos_juego::interpretar_como_entrada(const std::vector<std::string>& params, App_Juego_ObjetoJuego::Contenedor_objetos& contenedor)
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

void Factoria_objetos_juego::interpretar_como_salida(const std::vector<std::string>& params, App_Juego_ObjetoJuego::Contenedor_objetos& contenedor)
{
	if(params.size() != lp_salida)
	{
		throw Factoria_objetos_juego_excepcion(params.size(), lp_salida, "Salida");
	}
	else
	{
		const int x=toi(params[1]);
		const int y=toi(params[2]);
		contenedor.salida.reset( new Salida(x, y));

		auto ob=contenedor.salida.get();
		contenedor.objetos_juego.push_back(contenedor.salida);
		contenedor.colisionables.push_back(std::shared_ptr<Colisionable_I>(contenedor.salida, static_cast<Colisionable_I*>(ob)));
		contenedor.representables.push_back(std::shared_ptr<Representable_I>(contenedor.salida, static_cast<Representable_I*>(ob)));
	}
}

void Factoria_objetos_juego::interpretar_como_posicion_inicial(const std::vector<std::string>& params, App_Juego_ObjetoJuego::Contenedor_objetos& contenedor)
{
	if(params.size() != lp_posicion_inicial)
	{
		throw Factoria_objetos_juego_excepcion(params.size(), lp_posicion_inicial, "Posición inicial");
	}
	else
	{
		const int x=toi(params[1]);
		const int y=toi(params[2]);
		contenedor.posicion_inicial.reset( new Posicion_inicial(x, y));
	}
}
