#include "recogedor_bonus.h"

using namespace App_Juego;
Recogedor_bonus::Recogedor_bonus(App_Juego_Sistemas::Contador_tiempo& t, Jugador& j)
	:tiempo(t), jugador(j)
{

}

const App_Interfaces::Espaciable& Recogedor_bonus::obtener_espaciable_recogedor_bonus()const 
{
	return jugador;
}

bool Recogedor_bonus::puede_recoger_salud()
{
	return jugador.puede_recoger_salud();
}

void Recogedor_bonus::sumar_tiempo(float v) 
{
	tiempo.sumar_tiempo(v);
}

void Recogedor_bonus::sumar_salud(float v) 
{
	jugador.sumar_salud(v);
}
