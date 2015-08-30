#ifndef CONTEXTO_TURNO_I
#define CONTEXTO_TURNO_I

#include <vector>

/**
* Interface para un objeto que se pasaría a cualquier objeto que implemente
* "Con_turno_I". Incluye el contexto necesario que los objetos de juego pueden
* necesitar.
*/

namespace App_Interfaces
{

class Espaciable;

class Contexto_turno_I
{
	/////////////////////////
	//Interface pública.

	public:

	virtual						~Contexto_turno_I();
	virtual float					acc_delta() const=0;
	virtual const Espaciable&			acc_blanco() const=0;
	virtual bool					es_fuera_sala(const App_Interfaces::Espaciable&) const=0;
	virtual std::vector<const Espaciable *>		celdas_en_caja(const App_Interfaces::Espaciable&) const=0;

};
}

#endif
