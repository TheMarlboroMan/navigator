#include "logica_bonus.h"

#include "objetos_juego/bonus_tiempo.h"
#include "objetos_juego/bonus_salud.h"

using namespace App_Juego;
using namespace App_Juego_Sistemas;

Logica_bonus::Logica_bonus(Contador_tiempo& ct, Jugador& j)
	:contador_tiempo(ct), jugador(j)
{

}

void Logica_bonus::recoger_bonus_tiempo(App_Juego_ObjetoJuego::Bonus_tiempo& b)
{
	contador_tiempo.sumar_tiempo(b.acc_tiempo());
	b.mut_borrar(true);
}

void Logica_bonus::recoger_bonus_salud(App_Juego_ObjetoJuego::Bonus_salud& b)
{
	if(jugador.puede_recoger_salud())
	{
		jugador.sumar_salud(b.acc_salud());
		b.mut_borrar(true);
	}
}

