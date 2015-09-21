#ifndef DISPARABLE_I_H
#define DISPARABLE_I_H

/**
* Interface para objetos susceptibles de recibir disparos.
*
* Ojo a la herencia virtual de Objeto_juego_I.
*/

#include "objeto_juego_i.h"

namespace App_Interfaces
{

class Espaciable;

class Disparable_contexto_I
{
	public:
				~Disparable_contexto_I() {}
	virtual void		insertar_marcador(float val, float x, float y)=0;
};

class Disparable_I:
	public virtual Objeto_juego_I
{
	public:

				~Disparable_I() {}
	virtual void 		recibir_disparo(float potencia, Disparable_contexto_I&)=0;
	virtual bool		es_colision_proyectil(const Espaciable&)const=0;
};
}

#endif
