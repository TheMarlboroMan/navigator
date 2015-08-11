#ifndef DISPARABLE_I_H
#define DISPARABLE_I_H

/**
* Interface para objetos susceptibles de recibir disparos.
*
* Ojo a la herencia virtual de Objeto_juego_I.
*/

#include "objeto_juego_i.h"
#include "../visitantes/visitante_disparable.h"

namespace App_Interfaces
{

class Espaciable;

class Disparable_I:
	public virtual Objeto_juego_I
{
	public:

				~Disparable_I() {}
	virtual void 		recibir_visitante(App_Visitantes::Visitante_disparable& v)=0;
	virtual void 		recibir_disparo(float potencia)=0;
	virtual bool		es_colision_proyectil(const Espaciable&)const=0;
};
}

#endif
