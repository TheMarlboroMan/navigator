#ifndef LOGICA_GENERADOR_OBJETOS_JUEGO_H
#define LOGICA_GENERADOR_OBJETOS_JUEGO_H

#include <memory>
#include <vector>
#include "../../interfaces/generador_objetos_juego_i.h"
#include "../factorias/factoria_objetos_juego.h"
#include "../factorias/factoria_objetos_volatiles.h"
#include "../contenedores/contenedor_objetos.h"
#include "../contenedores/contenedor_volatiles.h"
#include "../../interfaces/factoria_objetos_juego_i.h"
#include "../jugador.h"

namespace App_Juego_Logica
{

class Interface_creador_objetos:
	public App_Interfaces::Factoria_objetos_juego_I
{
	public:

							Interface_creador_objetos(App_Juego_Contenedores::Contenedor_objetos&, App_Juego_Contenedores::Contenedor_volatiles&, App_Interfaces::Espaciable&, const App_Lectores::Info_obstaculos_genericos& iog);
	
	virtual void					fabricar_bonus_tiempo(float x, float y, float t);
	virtual void					fabricar_bonus_salud(float x, float y, float t);
	virtual void					fabricar_chispa(float x, float y, float tv, const DLibH::Vector_2d&);
	virtual void					fabricar_explosion(float x, float y, float tv, const DLibH::Vector_2d&);
	virtual void					fabricar_chatarra(float x, float y, float tv, const DLibH::Vector_2d&);
	virtual void					fabricar_fantasma_jugador(float x, float y, float tv, float ve, App_Definiciones::direcciones direccion);
	virtual void					fabricar_fantasma_bonus_salud(float x, float y, float tv, float ve);
	virtual void					fabricar_fantasma_bonus_tiempo(float x, float y, float tv, float ve);
	virtual void					fabricar_humo(float x, float y, float tv);
	virtual void					fabricar_proyectil_normal_enemigo(float x, float y, int w, int h, const DLibH::Vector_2d& v, float pot);
	virtual void					fabricar_proyectil_rayo_estatico_enemigo(float x, float y, int w, int h, float pot);
	virtual void					fabricar_trazador_humo(float x, float y, float tv, const DLibH::Vector_2d& v);

	virtual const App_Interfaces::Espaciable& 	acc_blanco_disparo() const {return espaciable;}

	//////////////
	//Internas.

	private:

	App_Juego_Factorias::Factoria_objetos_juego 		factoria;
	App_Juego_Factorias::Factoria_objetos_volatiles 	factoria_volatiles;
	App_Juego_Contenedores::Contenedor_volatiles&		contenedor_volatiles;
	const App_Interfaces::Espaciable&			espaciable;
};

class Logica_generador_objetos_juego
{
	/////////////////////
	// Interface pública.

	public:

							Logica_generador_objetos_juego(App_Juego::Jugador&, const App_Lectores::Info_obstaculos_genericos& iog);
	void 						procesar(std::vector<App_Interfaces::Generador_objetos_juego_I *> v);
	bool						hay_nuevos() const {return contenedor.objetos_juego.size();}
	bool						hay_volatiles() const {return contenedor_volatiles.size();}
	App_Juego_Contenedores::Contenedor_objetos&	acc_contenedor() {return contenedor;}
	App_Juego_Contenedores::Contenedor_volatiles&	acc_contenedor_volatiles() {return contenedor_volatiles;}

	/////////////
	// Internas.

	private:

	App_Juego::Jugador&						jugador;
	App_Juego_Contenedores::Contenedor_objetos 			contenedor;
	App_Juego_Contenedores::Contenedor_volatiles 			contenedor_volatiles;
	Interface_creador_objetos					interface_crear;
};

}

#endif
