#include <sstream>
#include "barra_indicadora.h"
#include "../recursos.h"

using namespace App_Graficos;

Barra_indicadora::Barra_indicadora(int x, int y, int vmax, int vact, const std::string& pnombre)
	:caja(DLibH::Herramientas_SDL::nuevo_sdl_rect(x, y, W, H), R, G, B),
	txt_nombre(DLibV::Gestor_superficies::obtener(App::Recursos_graficos::rs_fuente_base), pnombre),
	txt_cantidad(DLibV::Gestor_superficies::obtener(App::Recursos_graficos::rs_fuente_base), "100"),
	nombre(pnombre),
	w_max(W), valor_max(vmax), valor_actual(vact),
	tiempo_vigencia(-1.f)
{
	caja.establecer_alpha(192);
	txt_nombre.establecer_posicion(caja.acc_posicion());
	txt_cantidad.establecer_posicion(caja.acc_posicion());
	txt_cantidad.desplazar(-30, 0);
}

void Barra_indicadora::establecer_posicion(int x, int y)
{
	caja.ir_a(x, y);
	txt_nombre.ir_a(x, y);
}

void Barra_indicadora::establecer_dimensiones(unsigned int w, unsigned int h)
{
	caja.establecer_posicion(0, 0, w, h, DLibV::Representacion::FRECT_W | DLibV::Representacion::FRECT_H);
	w_max=w;
}


void Barra_indicadora::establecer_color(unsigned int r, unsigned int g, unsigned int b)
{
	caja.mut_rgb(r, g, b);
}

void Barra_indicadora::establecer_nombre(const std::string v)
{
	nombre=v;
	txt_nombre.asignar(nombre);
}

void Barra_indicadora::establecer_valor_max(int v)
{
	valor_max=v;
}

void Barra_indicadora::establecer_valor_actual(int v)
{
	valor_actual=v;

	std::stringstream ss;
	ss<<valor_actual;
	txt_cantidad.asignar(ss.str());
}

void Barra_indicadora::volcar(DLibV::Pantalla& pantalla)
{
	int wcalc=(valor_actual * w_max) / valor_max;
	caja.establecer_posicion(0, 0, wcalc, 0, DLibV::Representacion::FRECT_W);
	caja.volcar(pantalla);
	txt_nombre.volcar(pantalla);
	txt_cantidad.volcar(pantalla);
}

void Barra_indicadora::turno(float v)
{
	if(tiempo_vigencia > 0.0f)
	{
		tiempo_vigencia-=v;
		if(tiempo_vigencia < 0.0f) tiempo_vigencia=0.0f;
	}
}
