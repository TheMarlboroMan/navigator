#include "efecto_colision_recogedor.h"

using namespace App_Juego_Logica;

Efecto_colision_recogedor::Efecto_colision_recogedor(App_Juego_Sistemas::Contador_tiempo& t, App_Juego::Jugador& j)
	:salida_nivel(false), tiempo(t), jugador(j)
{

}

bool Efecto_colision_recogedor::puede_recoger_salud()
{
	return jugador.puede_recoger_salud();
}

void Efecto_colision_recogedor::sumar_tiempo(float v)
{
	tiempo.sumar_tiempo(v);
}

void Efecto_colision_recogedor::sumar_salud(float v)
{
	jugador.sumar_salud(v);
}

void Efecto_colision_recogedor::recibir_impacto(float v)
{
	jugador.recibir_impacto(v);
}
