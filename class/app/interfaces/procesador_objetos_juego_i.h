#ifndef PROCESADOR_OBJETOS_JUEGO_I
#define PROCESADOR_OBJETOS_JUEGO_I

/**
* Esta clase define una serie de objetos que pueden trabajar con vectores de
* objetos de juego. La idea es poder construir clases pequeñas con un poco
* de lógica dentro y pasarlas a la clase "Sala" para que las ejecute sobre
* sus objetos de juego.
*/

#include "objeto_juego_i.h"

namespace App_Interfaces
{
class Procesador_objetos_juego_I
{
	////////////////
	//Interface pública.
	public:
	typedef std::vector<std::shared_ptr<Objeto_juego_I>> vector_oj;

				~Procesador_objetos_juego_I() {}

	virtual void 		procesar(vector_oj v)=0;
	//TODO: Quizás podamos añadir un overload para vectores sin shared_ptr. Sería trivial, básicamente llamar de uno a otro.
};
}

#endif
