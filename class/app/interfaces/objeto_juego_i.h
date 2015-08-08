#ifndef OBJETO_JUEGO_I_H
#define OBJETO_JUEGO_I_H

#include "../visitantes/visitante_objeto_juego.h"
#include <iostream>

/**
* Interface que define un objeto de juego. Su objetivo es definir una clase
* base en la que meter todos los objetos de juego que luego puedan
* separarse usando un visitante.
*/

namespace App_Graficos
{
class Bloque_transformacion_representable;
}

namespace App_Interfaces
{

/**
* Facetador
*/

class Objeto_juego_I;
class Representable_I;
class Con_turno_I;
class Bonus_I;
class Espaciable;
class Disparable_I;
class Disparador_I;

struct Facetador
{
	Objeto_juego_I * 	objeto_juego;
	Representable_I * 	representable;
	Con_turno_I * 		con_turno;
	Bonus_I * 		bonus;
	Espaciable * 		espaciable;
	Disparable_I * 		disparable;
	Disparador_I * 		disparador;

	Facetador()
		:objeto_juego(nullptr), 
		representable(nullptr),
		con_turno(nullptr),
		bonus(nullptr),
		espaciable(nullptr),
		disparable(nullptr),
		disparador(nullptr)
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

	Facetador& mut_disparable(Disparable_I * v)
	{
		disparable=v;
		return *this;
	}

	Facetador& mut_disparador(Disparador_I * v)
	{
		disparador=v;
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

	private:

	Facetador 			facetador;
	bool 				borrar;

	friend bool 			es_representable(const Objeto_juego_I&);
	friend bool 			es_espaciable(const Objeto_juego_I&);
	friend bool 			es_con_turno(const Objeto_juego_I&);
	friend bool 			es_bonus(const Objeto_juego_I&);
	friend bool 			es_disparable(const Objeto_juego_I&);
	friend bool 			es_disparador(const Objeto_juego_I&);
};

bool es_representable(const Objeto_juego_I&);
bool es_espaciable(const Objeto_juego_I&);
bool es_con_turno(const Objeto_juego_I&);
bool es_bonus(const Objeto_juego_I&);
bool es_disparable(const Objeto_juego_I&);
bool es_disparador(const Objeto_juego_I&);

}

#endif
