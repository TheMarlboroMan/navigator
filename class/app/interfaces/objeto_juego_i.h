#ifndef OBJETO_JUEGO_I_H
#define OBJETO_JUEGO_I_H

#include "../visitantes/visitante_objeto_juego.h"

/**
* Interface que define un objeto de juego. Su objetivo es definir una clase
* base en la que meter todos los objetos de juego que luego puedan
* separarse usando un visitante.
*/

namespace App_Interfaces
{
class Objeto_juego_I
{
	public:

			Objeto_juego_I() {}
	virtual 	~Objeto_juego_I() {}

	virtual void 	recibir_visitante(App_Visitantes::Visitante_objeto_juego& v)=0;
	virtual void 	recibir_visitante(App_Visitantes::Visitante_objeto_juego_const& v)const=0;
};

}

#endif
