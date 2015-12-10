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

void Representador::generar_hud(DLibV::Pantalla& pantalla, Barra_indicadora& salud, Barra_indicadora& energia, Barra_indicadora& escudo, Barra_indicadora& enemigos, std::string tiempo)
{
	//Dibujar caja HUD...
	SDL_Rect cp=DLibH::Herramientas_SDL::nuevo_sdl_rect(X_FONDO_HUD, Y_FONDO_HUD, W_FONDO_HUD, H_FONDO_HUD);
	DLibV::Representacion_primitiva_caja CAJA(cp, 0, 0, 0);
	CAJA.hacer_estatica();
	CAJA.volcar(pantalla);

	//Dibujar barras...
	salud.volcar(pantalla);
	energia.volcar(pantalla);
	escudo.volcar(pantalla);
	if(enemigos.es_vigente()) enemigos.volcar(pantalla);

	DLibV::Representacion_texto_auto rep_hud(DLibV::Gestor_superficies::obtener(App::Recursos_graficos::rs_fuente_base), tiempo);
	rep_hud.asignar(tiempo);
	rep_hud.hacer_estatica();
	rep_hud.establecer_posicion(16, 464);
	rep_hud.volcar(pantalla);
}
