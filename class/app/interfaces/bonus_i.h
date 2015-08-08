#ifndef BONUS_I_H
#define BONUS_I_H

#include "../visitantes/visitante_bonus.h"

/**
* Interface para objetos susceptibles de recibir un visitante de bonus.
*/

namespace App_Interfaces
{
class Bonus_I
{
	public:

				~Bonus_I() {}
	virtual void 		recibir_visitante(App_Visitantes::Visitante_bonus& v)=0;
};
}

#endif
