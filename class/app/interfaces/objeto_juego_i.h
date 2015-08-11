#ifndef OBJETO_JUEGO_I_H
#define OBJETO_JUEGO_I_H

#include "../visitantes/visitante_objeto_juego.h"
#include <iostream>

/**
* Interface que define un objeto de juego. Su objetivo es definir una clase
* base en la que meter todos los objetos de juego que luego puedan
* separarse usando un visitante.
*/

namespace App_Interfaces
{
/**
* Interface en si.
*/

class Objeto_juego_I
{
	public:
					Objeto_juego_I();
	virtual 			~Objeto_juego_I() {}
	virtual bool			es_borrar()const {return borrar;}	
	virtual void			mut_borrar(bool v) {borrar=v;}


	/**
	* Toda la interface a implementar implica un nivel de ruido interesante
	* en el código, pero no hay mucho que podamos hacer al respecto.
	* Que existan estos métodos no significa que tengamos que implementar
	* un cuerpo para los mismos. Por ejemplo, algo no representable no
	* hará nada para transformar_bloque_representacion.
	*/

	virtual void 			recibir_visitante(App_Visitantes::Visitante_objeto_juego& v)=0;
	virtual void 			recibir_visitante(App_Visitantes::Visitante_objeto_juego_const& v)const=0;

	private:

	bool 				borrar;
};
}

#endif
