#ifndef RECOGE_BONUS_I
#define RECOGE_BONUS_I

/**
* Interface para una clase que hace la acción de recoger los bonus. No se 
* aplica a ningún actor de juego, más bien es un proxy conocido para los bonus
* sin que tengan que conocer detalles del jugador y demás.
*/

#include "espaciable.h"

namespace App_Interfaces
{

class Recoge_bonus_I
{
	///////////
	//Interface pública
	public:

	virtual const App_Interfaces::Espaciable&	obtener_espaciable_recogedor_bonus()const=0;
	virtual bool					puede_recoger_salud()=0;
	virtual void					sumar_tiempo(float)=0;
	virtual void					sumar_salud(float)=0;
};
}

#endif
