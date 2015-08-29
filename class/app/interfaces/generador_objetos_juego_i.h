#ifndef GENERADOR_OBJETOS_JUEGO_I
#define GENERADOR_OBJETOS_JUEGO_I

#include "objeto_juego_i.h"
#include "factoria_objetos_juego_i.h"

namespace App_Interfaces
{
class Generador_objetos_juego_I:
	public virtual Objeto_juego_I
{
	///////////////
	//Interface pública.
	public:

	virtual			~Generador_objetos_juego_I();
	virtual	void		generar_objetos(App_Interfaces::Factoria_objetos_juego_I&)=0;

	///////////////
	//Internas.
	private:
};
}

#endif
