#ifndef FACTORIA_OBJETOS_JUEGO_H
#define FACTORIA_OBJETOS_JUEGO_H

#include <stdexcept>
#include <vector>
#include <string>

#include "../../lectores/info_obstaculos_genericos.h"
#include "../contenedores/contenedor_objetos.h"
#include "../objetos_juego/bonus_salud.h"
#include "../objetos_juego/bonus_tiempo.h"
#include "../objetos_juego/enemigo_basico.h"
#include "../objetos_juego/enemigo_rebote.h"
#include "../objetos_juego/entrada.h"
#include "../objetos_juego/salida.h"
#include "../objetos_juego/posicion_inicial.h"
#include "../objetos_juego/obstaculo_generico.h"

namespace App_Juego_Factorias
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

//TODO: A la factoría hay que darle un repensado... Sería una buena cosa que simplemente
//fabricara los objetos y delegar a otra clase la interpretación de las líneas y el 
//guardado en el contenedor de objetos de turno.

class Factoria_objetos_juego
{	
	////////////////////
	//Interface pública.
	public:

							Factoria_objetos_juego(const App_Lectores::Info_obstaculos_genericos&);
	void						establecer_contenedor(App_Juego_Contenedores::Contenedor_objetos&);

	void 						interpretar_linea(const std::string&);

	void						insertar(std::shared_ptr<App_Juego_ObjetoJuego::Bonus_tiempo>&);
	void						insertar(std::shared_ptr<App_Juego_ObjetoJuego::Bonus_salud>&);
	void						insertar(std::shared_ptr<App_Juego_ObjetoJuego::Enemigo_basico>&);
	void						insertar(std::shared_ptr<App_Juego_ObjetoJuego::Enemigo_rebote>&);
	void						insertar(std::shared_ptr<App_Juego_ObjetoJuego::Salida>&);
	void						insertar(std::shared_ptr<App_Juego_ObjetoJuego::Obstaculo_generico>&);

	std::shared_ptr<App_Juego_ObjetoJuego::Bonus_tiempo>		crear_bonus_tiempo(float x, float y, float t);
	std::shared_ptr<App_Juego_ObjetoJuego::Bonus_salud>		crear_bonus_salud(float x, float y, float t);

	////////////////////
	//Métodos privados.
	private:

	int						toi(const std::string& c) {return std::atoi(c.c_str());}
	void						interpretar_como_bonus_tiempo(const std::vector<std::string>&);
	void						interpretar_como_bonus_salud(const std::vector<std::string>&);
	void						interpretar_como_enemigo_basico(const std::vector<std::string>&);
	void						interpretar_como_enemigo_rebote(const std::vector<std::string>&);
	void						interpretar_como_entrada(const std::vector<std::string>&);
	void						interpretar_como_salida(const std::vector<std::string>&);
	void						interpretar_como_posicion_inicial(const std::vector<std::string>&);
	void						interpretar_como_obstaculo_generico(const std::vector<std::string>&);

	///////////////////
	// Propiedades.

	private:

	App_Juego_Contenedores::Contenedor_objetos *	contenedor_ptr;
	const App_Lectores::Info_obstaculos_genericos&	info_obstaculos_genericos;

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
	static const int				lp_obstaculo_generico=4;

	enum tipos {
		entrada=1,
		posicion_inicial=2,
		salida=3,
		bonus_salud=10,
		bonus_tiempo=11,
		enemigo_basico=30,
		enemigo_rebote=31,
		obstaculo_generico=50
	};
};

}

#endif
