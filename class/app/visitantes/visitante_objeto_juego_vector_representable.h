#ifndef VISITANTE_OBJETO_JUEGO_VECTOR_REPRESENTABLE
#define VISITANTE_OBJETO_JUEGO_VECTOR_REPRESENTABLE

#include "visitante_objeto_juego.h"

namespace App_Visitantes
{
//TODO: Mover al punto donde se use...
class Visitante_objeto_juego_vector_representable:public Visitante_objeto_juego_const
{
	////////////////////
	//Interface pública.
	public:
	
	Visitante_objeto_juego_vector_representable(std::vector<const App_Graficos::Representable *>& pv)
		:v(pv)
	{}

//	virtual void 			visitar(App_Interfaces::Objeto_juego_interface&) {std::cout<<"VISITANTE CONST OBJ BASE"<<std::endl;}
	virtual void 			visitar(const App_Juego_ObjetoJuego::Bonus_tiempo& o) {v.push_back(&o);}

	///////////////////
	//Propiedades.
	private:

	std::vector<const App_Graficos::Representable *>& v;
};
}
#endif
