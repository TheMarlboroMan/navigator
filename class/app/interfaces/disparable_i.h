#ifndef DISPARABLE_I_H
#define DISPARABLE_I_H



/**
* Interface para objetos susceptibles de recibir disparos.
*/

namespace App_Interfaces
{
class Disparable_I
{
	public:

				~Disparable_I() {}
	virtual void 		recibir_disparo(float potencia)=0;
};
}

#endif
