#ifndef LOGICA_BONUS_H
#define LOGICA_BONUS_H

#include "sistemas/contador_tiempo.h"
#include "jugador.h"
#include "../visitantes/visitante_bonus.h"

/**
* Clase que controla la lógica de recoger los objetos del juego. Es una 
* extensión del visitante de bonus y combina tanto el double dispatcher como
* la lógica en si.
*/

namespace App_Juego_ObjetoJuego
{
class Bonus_tiempo;
class Bonus_salud;
}

namespace App_Juego
{
class Logica_bonus:public App_Visitantes::Visitante_bonus
{
	/////////////////
	//Interface pública.
	public:

	Logica_bonus(App_Juego_Sistemas::Contador_tiempo& ct, Jugador& j);

	/////////////////
	//Implementación de Visitante_bonus.
	public:

	virtual void 		visitar(App_Juego_ObjetoJuego::Bonus_tiempo& b);
	virtual void 		visitar(App_Juego_ObjetoJuego::Bonus_salud& b);

	/////////////////
	//Propiedades.
	private:

	App_Juego_Sistemas::Contador_tiempo&	contador_tiempo;
	Jugador& jugador;
};
}
#endif
