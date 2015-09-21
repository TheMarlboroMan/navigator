#include "particula_numero.h"

using namespace App_Juego_ObjetoJuego;

std::map<size_t, DLibV::Representacion_texto_auto_dinamica> Particula_numero::textos;

Particula_numero::Particula_numero(float x, float y, float tv, const DLibH::Vector_2d& v):
	Particula_movil_base(x, y, tv, v)
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
/*	if(!textos.count(numero))
	{
		textos.insert(std::make_pair<numero, 
			DLibV::Representacion_texto_auto_dinamica(
				nullptr, //TODO TODO TODO... Argh... El bloque tampoco tiene la pantalla.... ¿Dónde está la puta pantalla? b.acc_renderer(), 
				DLibV::Gestor_superficies::obtener(App::Recursos_graficos::rs_fuente_base), 
				std::itoa(numero)));
	}

	b.establecer_externa(textos.at(numero));
	float alpha=calcular_parcial_tiempo_vida(255);
	if(alpha < 0.0f) alpha=0.0f;
	b.establecer_alpha(alpha);
	b.establecer_posicion(acc_espaciable_x(), acc_espaciable_y(), 32, 32);
*/
}

void Particula_numero::turno(App_Interfaces::Contexto_turno_I& ct)
{
	Particula_movil_base::turno(ct);
}
