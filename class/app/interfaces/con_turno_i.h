#ifndef CON_TURNO_I
#define CON_TURNO_I

#include "objeto_juego_i.h"
#include "contexto_turno_i.h"

/**
* Interface para representar a aquellos objetos que tienen algo que hacer cada
* cierto tiempo. Además también vamos a usar esta interface para relacionar a
* los objetos con otras cosas del mundo, como el jugador u otras celdas.
* Para esta relación vamos a usar la combinación de visitante y procesador.
*
* Ojo a la herencia virtual de Objeto_juego_I.
*/

namespace App_Interfaces
{

class Con_turno_I:
	public virtual Objeto_juego_I
{
	////////////////////
	//Interface pública.

	public:
				~Con_turno_I() {}
	virtual void 		turno(App_Interfaces::Contexto_turno_I&)=0;
};

}

#endif
