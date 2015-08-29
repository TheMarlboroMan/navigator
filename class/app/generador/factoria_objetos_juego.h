#ifndef FACTORIA_OBJETOS_JUEGO_H
#define FACTORIA_OBJETOS_JUEGO_H

#include <stdexcept>
#include <vector>
#include <string>
#include <herramientas/herramientas/herramientas.h>
#include <herramientas/vector_2d/vector_2d.h>

#include "../juego/contenedores/contenedor_objetos.h"
#include "../juego/contenedores/contenedor_volatiles.h"
#include "../juego/objetos_juego/bonus_salud.h"
#include "../juego/objetos_juego/bonus_tiempo.h"
#include "../juego/objetos_juego/enemigo_basico.h"
#include "../juego/objetos_juego/enemigo_rebote.h"
#include "../juego/objetos_juego/entrada.h"
#include "../juego/objetos_juego/salida.h"
#include "../juego/objetos_juego/posicion_inicial.h"
#include "../juego/objetos_juego/particula_chispa.h"
#include "../juego/objetos_juego/particula_explosion.h"
#include "../juego/objetos_juego/particula_chatarra.h"
#include "../juego/objetos_juego/particula_fantasma.h"

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

							Factoria_objetos_juego();
	void						establecer_contenedor(App_Juego_Contenedores::Contenedor_objetos&);
	void						establecer_contenedor_volatiles(App_Juego_Contenedores::Contenedor_volatiles&);

	void 						interpretar_linea(const std::string&);

	void						insertar(std::shared_ptr<App_Juego_ObjetoJuego::Bonus_tiempo>&);
	void						insertar(std::shared_ptr<App_Juego_ObjetoJuego::Bonus_salud>&);
	void						insertar(std::shared_ptr<App_Juego_ObjetoJuego::Enemigo_basico>&);
	void						insertar(std::shared_ptr<App_Juego_ObjetoJuego::Enemigo_rebote>&);
	void						insertar(std::shared_ptr<App_Juego_ObjetoJuego::Salida>&);
	void						insertar(std::shared_ptr<App_Juego_ObjetoJuego::Particula_chispa>&);
	void						insertar(std::shared_ptr<App_Juego_ObjetoJuego::Particula_explosion>&);
	void						insertar(std::shared_ptr<App_Juego_ObjetoJuego::Particula_chatarra>&);
	void						insertar(std::shared_ptr<App_Juego_ObjetoJuego::Particula_fantasma>&);

	std::shared_ptr<App_Juego_ObjetoJuego::Bonus_tiempo>		crear_bonus_tiempo(float x, float y, float t);
	std::shared_ptr<App_Juego_ObjetoJuego::Bonus_salud>		crear_bonus_salud(float x, float y, float t);
	std::shared_ptr<App_Juego_ObjetoJuego::Particula_chispa>	crear_chispa(float x, float y, float tv, const DLibH::Vector_2d& v);
	std::shared_ptr<App_Juego_ObjetoJuego::Particula_explosion>	crear_explosion(float x, float y, float tv, const DLibH::Vector_2d& v);
	std::shared_ptr<App_Juego_ObjetoJuego::Particula_chatarra>	crear_chatarra(float x, float y, float tv, const DLibH::Vector_2d& v);
	std::shared_ptr<App_Juego_ObjetoJuego::Particula_fantasma>	crear_fantasma(float x, float y, float tv, float ve, App_Definiciones::direcciones direccion, int recurso, const DLibH::Caja<int, int>& recorte);


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

	///////////////////
	// Propiedades.

	private:

	App_Juego_Contenedores::Contenedor_objetos *	contenedor_ptr;
	App_Juego_Contenedores::Contenedor_volatiles *	contenedor_volatiles_ptr;

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
