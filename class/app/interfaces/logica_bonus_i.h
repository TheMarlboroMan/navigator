#ifndef LOGICA_BONUS_I_H
#define LOGICA_BONUS_I_H

//Forward declarations.
namespace App_Juego_ObjetoJuego
{
class Bonus_escudo;
class Bonus_tiempo;
}

namespace App_Interfaces
{



/**
* Interface para la clase que usará la lógica de bonus. Tiene sólo los métodos
* públicos a usar, para poder definir la clase e intercambiarla por otra si es
* necesario.
*/

class Logica_bonus_I
{
	public:

	virtual void recoger_bonus_tiempo(App_Juego_ObjetoJuego::Bonus_tiempo&)=0;
//	virtual void recoger_bonus_escudo(App_Juego_ObjetoJuego::Bonus_escudo&)=0;
};

}

#endif
