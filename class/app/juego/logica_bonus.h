#ifndef LOGICA_BONUS_H
#define LOGICA_BONUS_H

#include "sistemas/contador_tiempo.h"
#include "jugador.h"

/**
* Clase que controla la lógica de recoger los objetos del juego.
*/

namespace App_Juego_ObjetoJuego
{
class Bonus_tiempo;
class Bonus_salud;
}

namespace App_Juego
{
class Logica_bonus
{
	/////////////////
	//Interface pública.
	public:

	Logica_bonus(App_Juego_Sistemas::Contador_tiempo& ct, Jugador& j);

	/////////////////
	//Implementación de Logica_bonus_I
	virtual void 		recoger_bonus_tiempo(App_Juego_ObjetoJuego::Bonus_tiempo& b);
	virtual void 		recoger_bonus_salud(App_Juego_ObjetoJuego::Bonus_salud& b);

	/////////////////
	//Propiedades.
	private:
	App_Juego_Sistemas::Contador_tiempo&	contador_tiempo;
	Jugador& jugador;
};
}
#endif
