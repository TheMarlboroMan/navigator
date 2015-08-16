#ifndef FACTORIA_OBJETOS_JUEGO_H
#define FACTORIA_OBJETOS_JUEGO_H

#include <stdexcept>
#include <vector>
#include <string>
#include <herramientas/herramientas/herramientas.h>
#include "../juego/objetos_juego/contenedor_objetos_juego.h"
#include "../juego/objetos_juego/bonus_salud.h"
#include "../juego/objetos_juego/bonus_tiempo.h"
#include "../juego/objetos_juego/enemigo_basico.h"
#include "../juego/objetos_juego/enemigo_rebote.h"
#include "../juego/objetos_juego/entrada.h"
#include "../juego/objetos_juego/salida.h"
#include "../juego/objetos_juego/posicion_inicial.h"

namespace App_Generador
{

class Factoria_objetos_juego_excepcion:
	public std::runtime_error
{
	public:

	int 		longitud_parametros;
	int 		longitud_esperada;
	std::string 	tipo;

	Factoria_objetos_juego_excepcion(int lp, int le, const std::string& lt)
		:std::runtime_error("Error en factoria de objetos juego."), 
		longitud_parametros(lp),
		longitud_esperada(le),
		tipo(lt)
	{

	}
};

class Factoria_objetos_juego
{	
	////////////////////
	//Interface pública.
	public:

	void 						interpretar_linea(const std::string&, App_Juego_ObjetoJuego::Contenedor_objetos&);

	////////////////////
	//Métodos privados.
	private:

	int						toi(const std::string& c) {return std::atoi(c.c_str());}
	void						interpretar_como_bonus_tiempo(const std::vector<std::string>&, App_Juego_ObjetoJuego::Contenedor_objetos&);
	void						interpretar_como_bonus_salud(const std::vector<std::string>&, App_Juego_ObjetoJuego::Contenedor_objetos&);
	void						interpretar_como_enemigo_basico(const std::vector<std::string>&, App_Juego_ObjetoJuego::Contenedor_objetos&);
	void						interpretar_como_enemigo_rebote(const std::vector<std::string>&, App_Juego_ObjetoJuego::Contenedor_objetos&);
	void						interpretar_como_entrada(const std::vector<std::string>&, App_Juego_ObjetoJuego::Contenedor_objetos&);
	void						interpretar_como_salida(const std::vector<std::string>&, App_Juego_ObjetoJuego::Contenedor_objetos&);
	void						interpretar_como_posicion_inicial(const std::vector<std::string>&, App_Juego_ObjetoJuego::Contenedor_objetos&);

	///////////////////
	// Propiedades.

	private:

	/**
	* longitudes de parámetros.
	*/

	static const int				lp_entrada=4;
	static const int				lp_salida=3;
	static const int				lp_posicion_inicial=3;
	static const int				lp_bonus_salud=4;
	static const int				lp_bonus_tiempo=4;
	static const int				lp_enemigo_basico=4;
	static const int				lp_enemigo_rebote=6;

	enum tipos {
		entrada=1,
		posicion_inicial=2,
		salida=3,
		bonus_salud=10,
		bonus_tiempo=11,
		enemigo_basico=30,
		enemigo_rebote=31
	};
};

}

#endif
