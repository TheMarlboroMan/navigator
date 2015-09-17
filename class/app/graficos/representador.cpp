#include "representador.h"
#include "../recursos.h"

#include <sstream>

using namespace App_Graficos;
using namespace App_Interfaces;

Representador::Representador(const Animaciones& animaciones)
	:bloque_transformacion(animaciones)
{

}

unsigned int Representador::generar_vista(
	DLibV::Pantalla& pantalla, 
	DLibV::Camara& camara, 
	const std::vector<const Representable_I *>& v)
{
	unsigned int total=0;

	for(const Representable_I * r : v)
	{
		int ciclos=r->obtener_ciclos_representable(), c=1;
		while(c <= ciclos)
		{
			r->transformar_bloque(bloque_transformacion.mut_ciclo(c++));
			if(bloque_transformacion.rep->volcar(pantalla, camara)) ++total;
		}
		
	}

	return total;
}

unsigned int Representador::generar_vista(
	DLibV::Pantalla& pantalla, 
	const std::vector<const Representable_I *>& v)
{
	unsigned int total=0;

	for(const Representable_I * r : v)
	{
		int ciclos=r->obtener_ciclos_representable(), c=1;
		while(c <= ciclos)
		{
			r->transformar_bloque(bloque_transformacion.mut_ciclo(c++));
			if(bloque_transformacion.rep->volcar(pantalla)) ++total;
		}
	}

	return total;
}

void Representador::generar_hud(DLibV::Pantalla& pantalla, int salud, int energia, int escudo, std::string tiempo)
{
	//Dibujar caja HUD...
	SDL_Rect cp=DLibH::Herramientas_SDL::nuevo_sdl_rect(X_FONDO_HUD, Y_FONDO_HUD, W_FONDO_HUD, H_FONDO_HUD);
	DLibV::Representacion_primitiva_caja_estatica CAJA(cp, 0, 0, 0);
	CAJA.volcar(pantalla);

	//Dibujar barras...
	CAJA.establecer_alpha(192);
	CAJA.mut_rgb(192, 0, 0);
	CAJA.establecer_posicion(80, 416, salud, 10);
	CAJA.volcar(pantalla);

	CAJA.mut_rgb(0, 192, 0);
	CAJA.establecer_posicion(80, 427, energia, 10);
	CAJA.volcar(pantalla);

	CAJA.mut_rgb(0, 0, 192);
	CAJA.establecer_posicion(80, 438, escudo, 10);
	CAJA.volcar(pantalla);

	//Dibujar información.
	std::stringstream ss;
/*	ss<<jugador.acc_espaciable_x()<<","<<jugador.acc_espaciable_y()<<std::endl<<*/
	ss<<"HULL:   "<<salud<<"\nENERGY: "<<energia<<"\nSHIELD: "<<escudo;

	DLibV::Representacion_texto_auto_estatica rep_hud(pantalla.acc_renderer(), DLibV::Gestor_superficies::obtener(App::Recursos_graficos::rs_fuente_base), ss.str());
	rep_hud.mut_interlineado(2);
	rep_hud.establecer_posicion(16, 416);
	rep_hud.volcar(pantalla);

	rep_hud.asignar(tiempo);
	rep_hud.establecer_posicion(16, 464);
	rep_hud.volcar(pantalla);
}
