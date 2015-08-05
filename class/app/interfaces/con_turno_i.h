#ifndef CON_TURNO_I_H
#define CON_TURNO_I_H

/**
* Interface que define a aquellas cosas que deben actuar cada cierto
* tiempo. Se entiende la actuación como algo interno (por ejemplo, rebajar 
* contadores) ya que el método no da ninguna facilidad para comunicarse con
* el resto de las clases.
*/

namespace App_Interfaces
{

class Con_turno_I
{
	//////////////////
	//Interface pública:
	public:

	virtual ~Con_turno_I() {}
	virtual void turno(float delta)=0;
};

}

#endif
