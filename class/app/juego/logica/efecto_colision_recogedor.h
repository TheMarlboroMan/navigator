#ifndef EFECTO_COLISION_RECOGEDOR_H
#define EFECTO_COLISION_RECOGEDOR_H

#include "../../interfaces/efecto_colision_recogedor_i.h"
#include "../jugador.h"
#include "../sistemas/contador_tiempo.h"

namespace App_Juego_Logica
{

class Efecto_colision_recogedor:
	public App_Interfaces::Efecto_colision_recogedor_I
{
	//////////////////////////
	//Interface pública.

	public:

								Efecto_colision_recogedor(App_Juego_Sistemas::Contador_tiempo& t, App_Juego::Jugador& j);
	virtual const App_Interfaces::Espaciable&		obtener_espaciable()const {return jugador;}
	virtual bool						puede_recoger_salud();
	virtual void						sumar_tiempo(float v);
	virtual void						sumar_salud(float v);
	virtual void						recibir_impacto(float);
	virtual bool						es_jugador_aterrizado() const {return jugador.es_aterrizado();}
	virtual void						marcar_como_salida_nivel() {salida_nivel=true;}
	virtual bool						es_salida_nivel() const {return salida_nivel;}

	///////////////////////////
	//Internas...

	private:

	bool 							salida_nivel;
	App_Juego_Sistemas::Contador_tiempo& 			tiempo;
	App_Juego::Jugador&					jugador;
};

}
#endif
