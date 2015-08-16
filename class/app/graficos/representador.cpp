#include "representador.h"
#include "../recursos.h"

#include <sstream>

using namespace App_Graficos;
using namespace App_Interfaces;

unsigned int Representador::generar_vista(
	DLibV::Pantalla& pantalla, 
	DLibV::Camara& camara, 
	const std::vector<const Representable_I *>& v)
{
	unsigned int total=0;

	for(const Representable_I * r : v)
	{
		r->transformar_bloque(bloque_transformacion);
		if(bloque_transformacion.rep->volcar(pantalla, camara)) ++total;
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
		r->transformar_bloque(bloque_transformacion);
		if(bloque_transformacion.rep->volcar(pantalla)) ++total;
	}

	return total;
}

void Representador::dibujar_marco_automapa(DLibV::Pantalla&)
{
	//TODO...
}

void Representador::dibujar_pieza_automapa(DLibV::Pantalla& pantalla, int x, int y, App_Definiciones::direcciones t, bool es_actual)
{
	using namespace App;
	using namespace App_Definiciones;
	DLibV::Representacion_bitmap_estatica rep_bmp;
	rep_bmp.establecer_alpha(255);
	rep_bmp.establecer_modo_blend(DLibV::Representacion::BLEND_ALPHA);
	rep_bmp.establecer_textura(DLibV::Gestor_texturas::obtener(Recursos_graficos::RT_AUTOMAPA));
	rep_bmp.establecer_posicion(X_AUTOMAPA + (x * DIM_AUTOMAPA), 
			Y_AUTOMAPA + (y * DIM_AUTOMAPA), 
			DIM_AUTOMAPA, DIM_AUTOMAPA);

	//El fondo...

	int xfondo=es_actual ? 5 * DIM_AUTOMAPA : 0;
	rep_bmp.establecer_recorte(xfondo, 0, DIM_AUTOMAPA, DIM_AUTOMAPA);
	rep_bmp.volcar(pantalla);
	std::vector<direcciones> v {direcciones::arriba, direcciones::derecha, direcciones::abajo, direcciones::izquierda};


	for(direcciones val : v)
	{
		if( (t & val) != direcciones::nada)
		{
			
			switch(t & val)
			{
				case direcciones::arriba: rep_bmp.establecer_recorte(DIM_AUTOMAPA, 0, DIM_AUTOMAPA, DIM_AUTOMAPA); break;
				case direcciones::derecha: rep_bmp.establecer_recorte(2*DIM_AUTOMAPA, 0, DIM_AUTOMAPA, DIM_AUTOMAPA); break;
				case direcciones::abajo: rep_bmp.establecer_recorte(3*DIM_AUTOMAPA, 0, DIM_AUTOMAPA, DIM_AUTOMAPA); break;
				case direcciones::izquierda: rep_bmp.establecer_recorte(4*DIM_AUTOMAPA, 0, DIM_AUTOMAPA, DIM_AUTOMAPA); break;
				case direcciones::nada: break;
			}

			rep_bmp.volcar(pantalla);
		}
	}
}

void Representador::generar_hud(DLibV::Pantalla& pantalla, int salud, int energia, int escudo, std::string tiempo)
{
	//Dibujar caja HUD...
	SDL_Rect cp=DLibH::Herramientas_SDL::nuevo_sdl_rect(X_FONDO_HUD, Y_FONDO_HUD, W_FONDO_HUD, H_FONDO_HUD);
	DLibV::Representacion_primitiva_caja_estatica CAJA(cp, 0, 0, 0);
	CAJA.volcar(pantalla);

	//Dibujar información.
	std::stringstream ss;
/*	ss<<jugador.acc_espaciable_x()<<","<<jugador.acc_espaciable_y()<<std::endl<<*/
	ss<<"HULL: "<<salud<<"\nENERGY: "<<energia<<"\nSHIELD: "<<escudo;

	DLibV::Representacion_texto_auto_estatica rep_hud(pantalla.acc_renderer(), DLibV::Gestor_superficies::obtener(App::Recursos_graficos::RS_FUENTE_BASE), ss.str());
	rep_hud.establecer_posicion(16, 416);
	rep_hud.volcar(pantalla);

	rep_hud.asignar(tiempo);
	rep_hud.establecer_posicion(16, 464);
	rep_hud.volcar(pantalla);
}
