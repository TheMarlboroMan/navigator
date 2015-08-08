#ifndef CON_TURNO_I
#define CON_TURNO_I

#include "../visitantes/visitante_con_turno.h"

/**
* Interface para representar a aquellos objetos que tienen algo que hacer cada
* cierto tiempo. Además también vamos a usar esta interface para relacionar a
* los objetos con otras cosas del mundo, como el jugador u otras celdas.
* Para esta relación vamos a usar la combinación de visitante y procesador.
*/

//TODO: Convertir todas las interfaces a .o, para poder tratar mejor las
//depedencias.

namespace App_Interfaces
{

class Con_turno_I
{
	////////////////////
	//Interface pública.

	public:

				~Con_turno_I() {}
	virtual void 		turno(float)=0;
	virtual void		recibir_visitante(App_Visitantes::Visitante_con_turno& v)=0;
};

}

#endif
