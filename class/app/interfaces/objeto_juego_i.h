#ifndef OBJETO_JUEGO_I_H
#define OBJETO_JUEGO_I_H

#include "../visitantes/visitante_objeto_juego.h"
#include <iostream>

/**
* Interface que define un objeto de juego. Su objetivo es definir una clase
* base en la que meter todos los objetos de juego que luego puedan
* separarse usando un visitante.
* Dado el fracaso absoluto a la hora de usar un planteamiento por interfaces
* vamos a hacer que el objeto juego tenga todo lo que necesitamos (se puede
* borrar?, se puede representar?, tiene turno?) y otras películas más.
* Esto implica conocimiento de temas de representables y demás, pero bueno.
*/

namespace App_Graficos
{
class Bloque_transformacion_representable;
}

namespace App_Interfaces
{
/**
* Facetas...
*/

/*
enum class objeto_juego_facetas {nada=0, representable=1, __NADA__=2, espaciable=4, con_turno=8, bonus=16};
objeto_juego_facetas operator|(objeto_juego_facetas a, objeto_juego_facetas b);
objeto_juego_facetas operator&(objeto_juego_facetas a, objeto_juego_facetas b);
*/


/**
* Facetador
*/

class Objeto_juego_I;
class Representable_I;
class Con_turno_I;
class Bonus_I;
class Espaciable;

struct Facetador
{
	Objeto_juego_I * 	objeto_juego;
	Representable_I * 	representable;
	Con_turno_I * 		con_turno;
	Bonus_I * 		bonus;
	Espaciable * 		espaciable;

	Facetador()
		:objeto_juego(nullptr), 
		representable(nullptr),
		con_turno(nullptr),
		bonus(nullptr),
		espaciable(nullptr)
	{}

	Facetador& mut_objeto_juego(Objeto_juego_I * v)
	{
		objeto_juego=v;
		return *this;
	}

	Facetador& mut_representable(Representable_I * v)
	{
		representable=v;
		return *this;
	}

	Facetador& mut_bonus(Bonus_I * v)
	{
		bonus=v;
		return *this;
	}

	Facetador& mut_con_turno(Con_turno_I * v)
	{
		con_turno=v;
		return *this;
	}

	Facetador& mut_espaciable(Espaciable * v)
	{
		espaciable=v;
		return *this;
	}
};

/**
* Interface en si.
*/

class Objeto_juego_I
{
	public:
					Objeto_juego_I(const Facetador& f);
					Objeto_juego_I();
	virtual 			~Objeto_juego_I() {}
	virtual bool			es_borrar()const {return borrar;}	
	virtual Facetador&		como_facetador() {return facetador;}
	virtual const Facetador&	como_facetador() const {return facetador;}
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
//	virtual objeto_juego_facetas	obtener_facetas()const=0;

	private:

	Facetador facetador;
	bool borrar;
};

bool es_representable(const Objeto_juego_I&);
bool es_espaciable(const Objeto_juego_I&);
//bool es_borrable(const Objeto_juego_I&);
bool es_con_turno(const Objeto_juego_I&);
bool es_bonus(const Objeto_juego_I&);

}

#endif
