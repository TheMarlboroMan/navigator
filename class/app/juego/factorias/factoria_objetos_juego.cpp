#include "factoria_objetos_juego.h"

using namespace App_Juego_Factorias;
using namespace App_Juego_ObjetoJuego;
using namespace App_Interfaces;
using namespace DLibH;

Factoria_objetos_juego::Factoria_objetos_juego(const App_Lectores::Info_obstaculos_genericos& iog)
	:contenedor_ptr(nullptr), info_obstaculos_genericos(iog)
{

}

void Factoria_objetos_juego::establecer_contenedor(App_Juego_Contenedores::Contenedor_objetos& c)
{
	contenedor_ptr=&c;
}

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
			case enemigo_rebote:	interpretar_como_enemigo_rebote(params); break;
			case enemigo_tanque:	interpretar_como_enemigo_tanque(params); break;
			case entrada:		interpretar_como_entrada(params); break;
			case salida:		interpretar_como_salida(params); break;
			case posicion_inicial:	interpretar_como_posicion_inicial(params); break;
			case obstaculo_generico:	interpretar_como_obstaculo_generico(params); break;
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

void Factoria_objetos_juego::insertar(std::shared_ptr<App_Juego_ObjetoJuego::Bonus_tiempo>& ob)
{
	auto& contenedor=*contenedor_ptr;
	contenedor.objetos_juego.push_back(ob);
	contenedor.representables.push_back( std::shared_ptr<Representable_I>(ob, static_cast<Representable_I*>(ob.get())));
	contenedor.sonoros.push_back(std::shared_ptr<Sonoro_I>(ob, static_cast<Sonoro_I*>(ob.get())));
	contenedor.generadores_objetos_juego.push_back(std::shared_ptr<Generador_objetos_juego_I>(ob, static_cast<Generador_objetos_juego_I*>(ob.get())));
	contenedor.efectos_colision.push_back(std::shared_ptr<Efecto_colision_I>(ob, static_cast<Efecto_colision_I*>(ob.get())));
}

void Factoria_objetos_juego::insertar(std::shared_ptr<App_Juego_ObjetoJuego::Bonus_salud>& ob)
{
	auto& contenedor=*contenedor_ptr;
	contenedor.objetos_juego.push_back(ob);
	contenedor.representables.push_back(std::shared_ptr<Representable_I>(ob, static_cast<Representable_I*>(ob.get())));
	contenedor.efectos_colision.push_back(std::shared_ptr<Efecto_colision_I>(ob, static_cast<Efecto_colision_I*>(ob.get())));
	contenedor.sonoros.push_back(std::shared_ptr<Sonoro_I>(ob, static_cast<Sonoro_I*>(ob.get())));
	contenedor.generadores_objetos_juego.push_back(std::shared_ptr<Generador_objetos_juego_I>(ob, static_cast<Generador_objetos_juego_I*>(ob.get())));
}

void Factoria_objetos_juego::insertar(std::shared_ptr<App_Juego_ObjetoJuego::Enemigo_basico>& ob)
{
	auto& contenedor=*contenedor_ptr;
	contenedor.objetos_juego.push_back(ob);
	contenedor.efectos_colision.push_back(std::shared_ptr<Efecto_colision_I>(ob, static_cast<Efecto_colision_I*>(ob.get())));
	contenedor.representables.push_back(std::shared_ptr<Representable_I>(ob, static_cast<Representable_I*>(ob.get())));
	contenedor.sonoros.push_back(std::shared_ptr<Sonoro_I>(ob, static_cast<Sonoro_I*>(ob.get())));
	contenedor.con_turno.push_back(std::shared_ptr<Con_turno_I>(ob, static_cast<Con_turno_I*>(ob.get())));
	contenedor.disparables.push_back(std::shared_ptr<Disparable_I>(ob, static_cast<Disparable_I*>(ob.get())));
	contenedor.generadores_objetos_juego.push_back(std::shared_ptr<Generador_objetos_juego_I>(ob, static_cast<Generador_objetos_juego_I*>(ob.get())));
}

void Factoria_objetos_juego::insertar(std::shared_ptr<App_Juego_ObjetoJuego::Enemigo_tanque>& ob)
{
	auto& contenedor=*contenedor_ptr;
	contenedor.objetos_juego.push_back(ob);
	contenedor.efectos_colision.push_back(std::shared_ptr<Efecto_colision_I>(ob, static_cast<Efecto_colision_I*>(ob.get())));
	contenedor.representables.push_back(std::shared_ptr<Representable_I>(ob, static_cast<Representable_I*>(ob.get())));
	contenedor.sonoros.push_back(std::shared_ptr<Sonoro_I>(ob, static_cast<Sonoro_I*>(ob.get())));
	contenedor.con_turno.push_back(std::shared_ptr<Con_turno_I>(ob, static_cast<Con_turno_I*>(ob.get())));
	contenedor.disparables.push_back(std::shared_ptr<Disparable_I>(ob, static_cast<Disparable_I*>(ob.get())));
	contenedor.generadores_objetos_juego.push_back(std::shared_ptr<Generador_objetos_juego_I>(ob, static_cast<Generador_objetos_juego_I*>(ob.get())));
	//Hmmm TODO... Lo dejamos???. Si es así hay que quitar el efecto de colisión... Habría que arreglar lo de que el proyectil no choque contra el propio tanque.
	//contenedor.solidos.push_back( std::shared_ptr<Espaciable>(ob, static_cast<Espaciable*>(ob.get())));
}

void Factoria_objetos_juego::insertar(std::shared_ptr<App_Juego_ObjetoJuego::Enemigo_rebote>& ob)
{
	auto& contenedor=*contenedor_ptr;
	contenedor.objetos_juego.push_back(ob);
	contenedor.efectos_colision.push_back(std::shared_ptr<Efecto_colision_I>(ob, static_cast<Efecto_colision_I*>(ob.get())));
	contenedor.representables.push_back(std::shared_ptr<Representable_I>(ob, static_cast<Representable_I*>(ob.get())));
	contenedor.con_turno.push_back(std::shared_ptr<Con_turno_I>(ob, static_cast<Con_turno_I*>(ob.get())));
	contenedor.disparables.push_back(std::shared_ptr<Disparable_I>(ob, static_cast<Disparable_I*>(ob.get())));
}

void Factoria_objetos_juego::insertar(std::shared_ptr<App_Juego_ObjetoJuego::Salida>& ob)
{
	auto& contenedor=*contenedor_ptr;
	contenedor.objetos_juego.push_back(ob);
	contenedor.efectos_colision.push_back(std::shared_ptr<Efecto_colision_I>(ob, static_cast<Efecto_colision_I*>(ob.get())));
	contenedor.representables.push_back(std::shared_ptr<Representable_I>(ob, static_cast<Representable_I*>(ob.get())));
}

void Factoria_objetos_juego::insertar(std::shared_ptr<App_Juego_ObjetoJuego::Obstaculo_generico>& ob)
{
	auto& contenedor=*contenedor_ptr;
	contenedor.objetos_juego.push_back(ob);
	contenedor.solidos.push_back( std::shared_ptr<Espaciable>(ob, static_cast<Espaciable*>(ob.get())));
	contenedor.representables.push_back(std::shared_ptr<Representable_I>(ob, static_cast<Representable_I*>(ob.get())));
}

//////////////////////

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

		auto ob=crear_bonus_tiempo(x, y, cantidad);
		insertar(ob);
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
		insertar(ob);
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
		insertar(ob);
	}
}

void Factoria_objetos_juego::interpretar_como_enemigo_tanque(const std::vector<std::string>& params)
{
	if(params.size() != lp_enemigo_tanque)
	{
		throw Factoria_objetos_juego_excepcion(params.size(), lp_enemigo_tanque, "Enemigo tanque");
	}
	else
	{
		const int x=toi(params[1]);
		const int y=toi(params[2]);
		const int salud=toi(params[3]);
		std::shared_ptr<Enemigo_tanque> ob(new Enemigo_tanque(x, y, salud));
		insertar(ob);
	}
}

void Factoria_objetos_juego::interpretar_como_enemigo_rebote(const std::vector<std::string>& params)
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
		insertar(ob);
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
		contenedor_ptr->insertar_entrada(e);
	}
}

void Factoria_objetos_juego::interpretar_como_salida(const std::vector<std::string>& params)
{
	if(params.size() != lp_salida)
	{
		throw Factoria_objetos_juego_excepcion(params.size(), lp_salida, "Salida");
	}
	else
	{
		const int x=toi(params[1]);
		const int y=toi(params[2]);
		contenedor_ptr->salida.reset( new Salida(x, y));		
		insertar(contenedor_ptr->salida);
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
		contenedor_ptr->posicion_inicial.reset( new Posicion_inicial(x, y));
	}
}

void Factoria_objetos_juego::interpretar_como_obstaculo_generico(const std::vector<std::string>& params)
{
	if(params.size() != lp_obstaculo_generico)
	{
		throw Factoria_objetos_juego_excepcion(params.size(), lp_posicion_inicial, "Posición inicial");
	}
	else
	{
		const int x=toi(params[1]);
		const int y=toi(params[2]);
		const int tipo=toi(params[3]);

		std::shared_ptr<Obstaculo_generico> ob(new Obstaculo_generico(x, y, tipo, info_obstaculos_genericos));
		insertar(ob);
	}
}

std::shared_ptr<App_Juego_ObjetoJuego::Bonus_tiempo> Factoria_objetos_juego::crear_bonus_tiempo(float x, float y, float t)
{
	auto res=std::shared_ptr<Bonus_tiempo>(new Bonus_tiempo(x, y, t));
	return res;
}

std::shared_ptr<App_Juego_ObjetoJuego::Bonus_salud> Factoria_objetos_juego::crear_bonus_salud(float x, float y, float t)
{
	auto res=std::shared_ptr<Bonus_salud>(new Bonus_salud(x, y, t));
	return res;
}
