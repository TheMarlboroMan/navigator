#ifndef BONUS_I_H
#define BONUS_I_H

#include "../visitantes/visitante_bonus.h"
#include "objeto_juego_i.h"

/**
* Interface para objetos susceptibles de recibir un visitante de bonus.
* Incluye un método a implementar para saber si está en colisión con un 
* espaciable y si, por tanto, puede ser recogido.
*
* Ojo a la herencia de Objeto_juego_I: es virtual porque hay más interfaces
* que van a extender al objeto juego.
*/

namespace App_Interfaces
{

class Espaciable;

class Bonus_I:
	public virtual Objeto_juego_I
{
	public:

				~Bonus_I() {}
	virtual void 		recibir_visitante(App_Visitantes::Visitante_bonus& v)=0;
	virtual bool		es_bonus_para(const Espaciable&)const=0;
};
}

#endif
