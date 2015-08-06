#include "logica_bonus.h"

#include "objetos_juego/bonus_tiempo.h"
#include "objetos_juego/bonus_salud.h"

using namespace App_Juego;
using namespace App_Juego_Sistemas;

Logica_bonus::Logica_bonus(Contador_tiempo& ct, Jugador& j)
	:contador_tiempo(ct), jugador(j)
{

}

/**
* Cuando estamos llamando a cualquiera de estas fases hemos llegado al punto
* en que la colisión con el bonus está verificada y sólo tenemos que correr
* la lógica de turno.
*/

void Logica_bonus::visitar(App_Juego_ObjetoJuego::Bonus_tiempo& b)
{
	contador_tiempo.sumar_tiempo(b.acc_tiempo());
	b.mut_borrar(true);
}

void Logica_bonus::visitar(App_Juego_ObjetoJuego::Bonus_salud& b)
{
	if(jugador.puede_recoger_salud())
	{
		jugador.sumar_salud(b.acc_salud());
		b.mut_borrar(true);
	}
}

