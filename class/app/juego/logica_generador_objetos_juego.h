#ifndef LOGICA_GENERADOR_OBJETOS_JUEGO_H
#define LOGICA_GENERADOR_OBJETOS_JUEGO_H

#include <memory>
#include <vector>
#include "../interfaces/generador_objetos_juego_i.h"
#include "../generador/factoria_objetos_juego.h"
#include "contenedores/contenedor_objetos.h"
#include "../interfaces/factoria_objetos_juego_i.h"

namespace App_Juego
{

class Interface_creador_objetos:
	public App_Interfaces::Factoria_objetos_juego_I
{
	public:

	void						establecer_contenedor(App_Juego_Contenedores::Contenedor_objetos&);
	void						establecer_contenedor_volatiles(App_Juego_Contenedores::Contenedor_volatiles&);
	
	virtual void					fabricar_bonus_tiempo(float x, float y, float t);
	virtual void					fabricar_bonus_salud(float x, float y, float t);
	virtual void					fabricar_chispa(float x, float y, float tv, const DLibH::Vector_2d&);
	virtual void					fabricar_explosion(float x, float y, float tv, const DLibH::Vector_2d&);
	virtual void					fabricar_chatarra(float x, float y, float tv, const DLibH::Vector_2d&);
	virtual void					fabricar_fantasma(float x, float y, float tv, float ve, App_Definiciones::direcciones direccion, int recurso, const DLibH::Caja<int, int>& recorte);


	//////////////
	//Internas.

	private:

	App_Generador::Factoria_objetos_juego 		factoria;
};

class Logica_generador_objetos_juego
{
	/////////////////////
	// Interface pública.

	public:

							Logica_generador_objetos_juego(std::vector<std::shared_ptr<App_Interfaces::Generador_objetos_juego_I>>&, App_Interfaces::Generador_objetos_juego_I&);
	void 						procesar(std::vector<std::shared_ptr<App_Interfaces::Generador_objetos_juego_I>> v);
	bool						hay_nuevos() const {return contenedor.objetos_juego.size();}
	bool						hay_volatiles() const {return contenedor_volatiles.size();}
	App_Juego_Contenedores::Contenedor_objetos&	acc_contenedor() {return contenedor;}
	App_Juego_Contenedores::Contenedor_volatiles&	acc_contenedor_volatiles() {return contenedor_volatiles;}

	/////////////
	// Internas.

	private:

	std::vector<std::shared_ptr<App_Interfaces::Generador_objetos_juego_I>>&	generadores;
	App_Interfaces::Generador_objetos_juego_I&			jugador;
	Interface_creador_objetos					interface_crear;
	App_Juego_Contenedores::Contenedor_objetos 			contenedor;
	App_Juego_Contenedores::Contenedor_volatiles 			contenedor_volatiles
;
};

}

#endif
