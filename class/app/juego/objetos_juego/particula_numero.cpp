#include "particula_numero.h"

using namespace App_Juego_ObjetoJuego;

std::map<size_t, DLibV::Representacion_texto_auto_dinamica> Particula_numero::textos;

Particula_numero::Particula_numero(float x, float y, float tv, size_t val, App_Definiciones::colores::colores_texto col, const DLibH::Vector_2d& v):
	Particula_movil_base(x, y, tv, v),
	numero(val),
	color(col)
{

}

unsigned short int Particula_numero::obtener_profundidad_ordenacion()const
{
	return 30;
}

unsigned int Particula_numero::obtener_ciclos_representable()const
{
	return 1;
}

void Particula_numero::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	if(!textos.count(numero))
	{
		std::stringstream ss;
		ss<<numero;

		textos.insert(std::make_pair(numero, DLibV::Representacion_texto_auto_dinamica(
				DLibV::Gestor_superficies::obtener(App::Recursos_graficos::rs_fuente_base), 
				ss.str() ) ) );
	}

	b.establecer_externa(textos.at(numero));

	switch(color)
	{
		case App_Definiciones::colores::colores_texto::blanco: b.establecer_mod_color(255, 255, 255); break;
		case App_Definiciones::colores::colores_texto::rojo: b.establecer_mod_color(255, 0, 0); break;
		case App_Definiciones::colores::colores_texto::verde: b.establecer_mod_color(0, 255, 0); break;
		case App_Definiciones::colores::colores_texto::azul: b.establecer_mod_color(0, 0, 255); break;
	}

	float alpha=calcular_parcial_tiempo_vida(255);
	if(alpha < 0.0f) alpha=0.0f;

	const auto& c=textos.at(numero).acc_posicion();

	b.establecer_alpha(alpha);
	b.establecer_posicion(acc_espaciable_x(), acc_espaciable_y(), c.w, c.h);
}

void Particula_numero::turno(App_Interfaces::Contexto_turno_I& ct)
{
	Particula_movil_base::turno(ct);
}
