#ifndef RECOGEDOR_BONUS_I
#define RECOGEDOR_BONUS_I

#include "../../interfaces/recoge_bonus_i.h"
#include "../jugador.h"
#include "../sistemas/contador_tiempo.h"

namespace App_Juego_Logica
{
class Recogedor_bonus:
	public App_Interfaces::Recoge_bonus_I
{
	/////////////////
	//Interface pública.
	public:
								Recogedor_bonus(App_Juego_Sistemas::Contador_tiempo& t, App_Juego::Jugador& j);
	virtual const App_Interfaces::Espaciable&		obtener_espaciable_recogedor_bonus()const;
	virtual bool						puede_recoger_salud();
	virtual void						sumar_tiempo(float v);
	virtual void						sumar_salud(float v);

	/////////////////
	//Internas.
	private:

	App_Juego_Sistemas::Contador_tiempo& 			tiempo;
	App_Juego::Jugador&					jugador;
};
}

#endif
