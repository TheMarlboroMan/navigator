#include "particula_base.h"

using namespace App_Juego_ObjetoJuego;

HerramientasProyecto::Tabla_sprites Particula_base::tabla_sprites("data/recursos/particulas.dat");

Particula_base::Particula_base(float tv)
	:tiempo_vida(tv), tiempo_vida_inicial(tv)
{

}

Particula_base::~Particula_base()
{

}

void Particula_base::restar_tiempo_vida(float v) 
{
	tiempo_vida-=v;
	if(tiempo_vida <= 0.0f) mut_borrar(true);
}

/**
* @param int t
* Calcula cuantas fracciones de t han pasado si t es el tiempo de vida original
* de la partícula.
*/

int Particula_base::calcular_parcial_tiempo_vida(float t) const
{
	//TODO: Esta función no me gusta todo lo que debería... El primer paso es
	//"t" pero luego ya no.
	return ceil( (tiempo_vida * t) / tiempo_vida_inicial);
}
