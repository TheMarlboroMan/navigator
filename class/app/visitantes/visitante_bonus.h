#ifndef VISITANTE_BONUS
#define VISITANTE_BONUS

#include <iostream>

//Forward declarations de los objetos de turno.
namespace App_Interfaces
{
class Bonus_I;
}

namespace App_Juego_ObjetoJuego
{
class Bonus_tiempo;
class Bonus_salud;
}

namespace App_Visitantes
{

/*
* Se definen únicamente el tipo de visitante no const.
*/

class Visitante_bonus
{
	public:
	virtual void visitar(App_Juego_ObjetoJuego::Bonus_tiempo&)=0;
	virtual void visitar(App_Juego_ObjetoJuego::Bonus_salud&)=0;
};

}
#endif
