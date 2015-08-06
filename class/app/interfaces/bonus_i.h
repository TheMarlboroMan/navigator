#ifndef BONUS_I
#define BONUS_I

#include "../visitantes/visitante_bonus.h"

namespace App_Interfaces
{

//Forward declaration de espaciable.
class Espaciable;

class Bonus_I
{
	public:
	virtual ~Bonus_I() {}

	virtual void 	recibir_visitante(App_Visitantes::Visitante_bonus& v)=0;
	virtual bool	bonus_en_colision_con(const Espaciable&)=0;
};
}

#endif
