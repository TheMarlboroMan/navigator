#ifndef VISITANTE_OBJETO_JUEGO_FACETAS
#define VISITANTE_OBJETO_JUEGO_FACETAS

#include "visitante_objeto_juego.h"

namespace App_Visitantes
{

/*
* Definición de las distintas facetas que puede tener un objeto de juego. 
* Las facetas per se no son parte del objeto, sino propiedades que interpreta
* un visitante.
*/

enum class objeto_juego_facetas {nada=0, representable=1, colisionable=2};

objeto_juego_facetas operator|(objeto_juego_facetas a, objeto_juego_facetas b)
{
	return static_cast<objeto_juego_facetas>(static_cast<int>(a) | static_cast<int>(b));
}

objeto_juego_facetas operator&(objeto_juego_facetas a, objeto_juego_facetas b)
{
	return static_cast<objeto_juego_facetas>(static_cast<int>(a) & static_cast<int>(b));
}

/*
* El visitante que interpreta las facetas. Como vamos a tener visitante 
* constante y no constante y ambos hacen lo mismo vamos a tener varias funciones
* que extraigan las facetas y ambos las llamarán a esa.
*/

objeto_juego_facetas extraer(const App_Juego_ObjetoJuego::Bonus_tiempo)
{
	return objeto_juego_facetas::representable | objeto_juego_facetas::colisionable;
}

class Visitante_objeto_juego_facetas:public Visitante_objeto_juego
{
	////////////////////
	//Interface pública.
	public:
	
	Visitante_objeto_juego_facetas()
		:facetas(objeto_juego_facetas::nada)
	{}

//	virtual void 			visitar(App_Interfaces::Objeto_juego_interface&) {std::cout<<"VISITANTE CONST OBJ BASE"<<std::endl;}
	virtual void 			visitar(App_Juego_ObjetoJuego::Bonus_tiempo& o) {facetas=extraer(o);}

	objeto_juego_facetas		acc_facetas() const {return facetas;}
	void				reset() {facetas=objeto_juego_facetas::nada;}

	///////////////////
	//Propiedades.
	private:
	objeto_juego_facetas 		facetas;

};

class Visitante_objeto_juego_facetas_const:public Visitante_objeto_juego_const
{
	////////////////////
	//Interface pública.
	public:
	
	Visitante_objeto_juego_facetas_const()
		:facetas(objeto_juego_facetas::nada)
	{}

//	virtual void 			visitar(const App_Interfaces::Objeto_juego_interface&) {std::cout<<"VISITANTE CONST OBJ BASE"<<std::endl;}
	virtual void 			visitar(const App_Juego_ObjetoJuego::Bonus_tiempo& o) {facetas=extraer(o);}

	objeto_juego_facetas		acc_facetas() const {return facetas;}
	void				reset() {facetas=objeto_juego_facetas::nada;}

	///////////////////
	//Propiedades.
	private:
	objeto_juego_facetas 		facetas;

};
}
#endif
