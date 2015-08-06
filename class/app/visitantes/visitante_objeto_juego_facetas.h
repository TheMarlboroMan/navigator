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

enum class objeto_juego_facetas 
{
	nada=0, 
	representable=1, 
	borrable=2, 
	bonus=4,
	con_turno=8
};

objeto_juego_facetas operator|(objeto_juego_facetas a, objeto_juego_facetas b);
objeto_juego_facetas operator&(objeto_juego_facetas a, objeto_juego_facetas b);

/*
* El visitante que interpreta las facetas. Como vamos a tener visitante 
* constante y no constante y ambos hacen lo mismo vamos a tener varias funciones
* que extraigan las facetas y ambos las llamarán a esa.
*/


class Visitante_objeto_juego_facetas_base
{
	public:	
	objeto_juego_facetas 		facetas;
					Visitante_objeto_juego_facetas_base(): facetas(objeto_juego_facetas::nada) {}
	void				reset() {facetas=objeto_juego_facetas::nada;}
	objeto_juego_facetas 		extraer(const App_Juego_ObjetoJuego::Bonus_tiempo&) 	{return objeto_juego_facetas::representable | objeto_juego_facetas::borrable | objeto_juego_facetas::bonus;}
	objeto_juego_facetas 		extraer(const App_Juego_ObjetoJuego::Bonus_salud&) 	{return objeto_juego_facetas::representable | objeto_juego_facetas::borrable | objeto_juego_facetas::bonus;}
	objeto_juego_facetas 		extraer(const App_Juego_ObjetoJuego::Enemigo_basico&) 	{return objeto_juego_facetas::representable | objeto_juego_facetas::borrable | objeto_juego_facetas::con_turno;}
};

class Visitante_objeto_juego_facetas:
	public Visitante_objeto_juego, 
	public Visitante_objeto_juego_facetas_base
{
	////////////////////
	//Interface pública.
	public:
	
					Visitante_objeto_juego_facetas():Visitante_objeto_juego_facetas_base() {}
	virtual void 			visitar(App_Juego_ObjetoJuego::Bonus_tiempo& o) {facetas=extraer(o);}
	virtual void 			visitar(App_Juego_ObjetoJuego::Bonus_salud& o) {facetas=extraer(o);}
	virtual void 			visitar(App_Juego_ObjetoJuego::Enemigo_basico& o) {facetas=extraer(o);}
};

class Visitante_objeto_juego_facetas_const:
	public Visitante_objeto_juego_const, 
	public Visitante_objeto_juego_facetas_base
{
	////////////////////
	//Interface pública.
	public:
	
					Visitante_objeto_juego_facetas_const():Visitante_objeto_juego_facetas_base() {}
	virtual void 			visitar(const App_Juego_ObjetoJuego::Bonus_tiempo& o) {facetas=extraer(o);}
	virtual void 			visitar(const App_Juego_ObjetoJuego::Bonus_salud& o) {facetas=extraer(o);}
	virtual void 			visitar(const App_Juego_ObjetoJuego::Enemigo_basico& o) {facetas=extraer(o);}
};
}
#endif
