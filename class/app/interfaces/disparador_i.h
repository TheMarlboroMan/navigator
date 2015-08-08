#ifndef DISPARADOR_I_H
#define DISPARADOR_I_H

#include "../visitantes/visitante_disparador.h"

/**
* La interface para todos aquellos objetos del juego que pueden disparar. 
* Tendrán una bandera que indica si deben disparar y el método para recibir
* su visitante específico.
*/

namespace App_Interfaces
{
class Disparador_I
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
