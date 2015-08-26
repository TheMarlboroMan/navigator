#ifndef LOGICA_BONUS_H
#define LOGICA_BONUS_H

#include <vector>
#include <memory>
#include "../interfaces/bonus_i.h"
#include "../interfaces/recoge_bonus_i.h"

/**
* Clase que controla la lógica de recoger los objetos del juego. Implementa el
* método "procesar", requerido por las salas para usar sus "bonus_i".
*/

namespace App_Juego
{
class Logica_bonus
{
	/////////////////
	//Interface pública.
	public:

						Logica_bonus(App_Interfaces::Recoge_bonus_I&);
	virtual void 				procesar(std::vector<std::shared_ptr<App_Interfaces::Bonus_I>>&);

	/////////////////
	//Propiedades.
	private:

	App_Interfaces::Recoge_bonus_I&		recoge_bonus;
};

}
#endif
