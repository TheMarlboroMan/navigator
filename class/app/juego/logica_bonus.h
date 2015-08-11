#ifndef LOGICA_BONUS_H
#define LOGICA_BONUS_H

#include "sistemas/contador_tiempo.h"
#include "../visitantes/visitante_bonus.h"
#include "objetos_juego/bonus_salud.h"
#include "objetos_juego/bonus_tiempo.h"
#include "jugador.h"

/**
* Clase que controla la lógica de recoger los objetos del juego. Es una 
* extensión del visitante de bonus y combina tanto el double dispatcher como
* la lógica en si.
*/

namespace App_Juego
{
class Logica_bonus:
	public App_Visitantes::Visitante_bonus
{
	/////////////////
	//Interface pública.
	public:

	Logica_bonus(App_Juego_Sistemas::Contador_tiempo& ct, Jugador& j);
	virtual void 		procesar(std::vector<std::shared_ptr<App_Interfaces::Bonus_I>>&);

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
