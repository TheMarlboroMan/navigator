#ifndef COLISIONABLE_I_H
#define COLISIONABLE_I_H

#include "../visitantes/visitante_colisionable.h"
#include "objeto_juego_i.h"

/**
* Interface para los objetos de juego con los cuales colisionar implica un 
* efecto. La separación de esta interface de Bonus_I es simplemente por tener
* separados los efectos "positivos" del resto.
*
* Ojo a la herencia de Objeto_juego_I: es virtual porque hay más interfaces
* que van a extender al objeto juego.
*/

namespace App_Interfaces
{

class Espaciable;

class Colisionable_I:
	public virtual Objeto_juego_I
{
	public:

				~Colisionable_I() {}
	virtual void 		recibir_visitante(App_Visitantes::Visitante_colisionable& v)=0;
	virtual bool		es_colision_para(const Espaciable&)const=0;
};
}


#endif
