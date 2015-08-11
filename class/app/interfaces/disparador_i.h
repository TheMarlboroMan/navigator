#ifndef DISPARADOR_I_H
#define DISPARADOR_I_H

#include "../visitantes/visitante_disparador.h"
#include "objeto_juego_i.h"

/**
* La interface para todos aquellos objetos del juego que pueden disparar. 
* Tendrán una bandera que indica si deben disparar y el método para recibir
* su visitante específico.
*
* Ojo a la herencia de Objeto_juego_I.
*/

namespace App_Interfaces
{
class Disparador_I:
	public virtual Objeto_juego_I
{
	////////////////
	//Interface pública.
	public:
	
			~Disparador_I() {}
			Disparador_I();

	bool 		es_disparar() const {return disparar;}
	void		mut_disparar(bool v) {disparar=v;}
	virtual void 	recibir_visitante(App_Visitantes::Visitante_disparador& v)=0;

	/////////////////
	//Propiedades privadas.
	private:

	bool disparar;
};
}

#endif
