#include "logica_bonus.h"

using namespace App_Juego;
using namespace App_Juego_Sistemas;

Logica_bonus::Logica_bonus(Contador_tiempo& ct)
	:contador_tiempo(ct)
{

}

void Logica_bonus::recoger_bonus_tiempo(App_Juego_ObjetoJuego::Bonus_tiempo& b)
{
	contador_tiempo.sumar_tiempo(b.acc_tiempo());
	b.mut_borrar(true);
}
/*
void Logica_bonus::recoger_bonus_escudo(App_Juego_ObjetoJuego::Bonus_escudo&)
{

}
*/
