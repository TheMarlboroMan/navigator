#ifndef VISITANTE_OBJETO_JUEGO
#define VISITANTE_OBJETO_JUEGO

#include <iostream>

//Forward declarations de todos los objetos.
namespace App_Interfaces
{
class Objeto_juego_interface;
}

namespace App_Juego_ObjetoJuego
{
class Bonus_tiempo;
class Bonus_salud;
}


namespace App_Visitantes
{

/*
* Se definen dos tipos de visitantes: el "const" y el "no const". 
* El const se usará para pasar objetos que deben ser constantes
* y el no const justo para lo contrario.
* Los métodos son virtuales, pero no abstractos, para no tener
* que definir la escalera entera en cada uno de los visitantes
* derivados que vayamos a escribir.
*/

class Visitante_objeto_juego_const
{
	public:
//	virtual void visitar(const App_Interfaces::Objeto_juego_interface&) {std::cout<<"VISITANTE CONST OBJ BASE"<<std::endl;}
//	virtual void visitar(const App_Juego_ObjetoJuego::Bonus_tiempo&) {std::cout<<"VISITANTE CONST OBJ BONUS TIEMPO"<<std::endl;}
//	virtual void visitar(const App_Juego_ObjetoJuego::Bonus_salud&) {std::cout<<"VISITANTE CONST OBJ BONUS SALUD"<<std::endl;}
	virtual void visitar(const App_Juego_ObjetoJuego::Bonus_tiempo&)=0;
	virtual void visitar(const App_Juego_ObjetoJuego::Bonus_salud&)=0;
};

class Visitante_objeto_juego
{
	public:
//	virtual void visitar(App_Interfaces::Objeto_juego_interface&) {std::cout<<"VISITANTE OBJ BASE"<<std::endl;}	
//	virtual void visitar(App_Juego_ObjetoJuego::Bonus_tiempo&)=0; {std::cout<<"VISITANTE OBJ BONUS TIEMPO"<<std::endl;}
//	virtual void visitar(App_Juego_ObjetoJuego::Bonus_salud&)=0; {std::cout<<"VISITANTE OBJ BONUS SALUD"<<std::endl;}
	virtual void visitar(App_Juego_ObjetoJuego::Bonus_tiempo&)=0;
	virtual void visitar(App_Juego_ObjetoJuego::Bonus_salud&)=0;
};

}
#endif
