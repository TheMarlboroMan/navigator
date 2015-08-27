#ifndef ALPHA_PROTOTIPO_H
#define ALPHA_PROTOTIPO_H

#include "../../interfaces/factoria_objetos_juego_i.h"

/**
* La base para los prototipos a partir de los cuales se crean objetos de juego.
*/

namespace App_Juego_Prototipos
{
class Alpha_prototipo
{
	//////////////////////
	//Interface pública.

	public:

	virtual			~Alpha_prototipo();
	
	/**
	* Esta función se sobreescribe en todos los prototipos para crear el objeto...
	* Lo complicado será que el objeto tendrá que insertarse en algún tipo de
	* contenedor mediante una factoría... Lo ideal sería recibir la factoría
	* en si mediante una interface o algo.
	*/

	virtual void		crear_objeto_juego(App_Interfaces::Factoria_objetos_juego_I&)=0;	
};
}

#endif
