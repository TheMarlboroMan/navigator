#ifndef BONUS_I
#define BONUS_I

#include "../visitantes/visitante_bonus.h"

namespace App_Interfaces
{
class Bonus_I
{
	public:
	virtual ~Bonus_I() {}

	//TODO: Quizás, mejor que visitante_bonus sea una interface Logica_bonus_I....
	virtual void 	recibir_visitante(App_Visitantes::Visitante_bonus& v)=0;
};
}

#endif
