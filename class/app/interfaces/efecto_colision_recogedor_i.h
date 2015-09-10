#ifndef EFECTO_COLISION_RECOGEDOR_I_H
#define EFECTO_COLISION_RECOGEDOR_I_H

/**
* Interface para una clase que hace la acción de recoger las consecuencias. 
* de las colisiones del jugador con otros objetos del juego. No se  aplica a 
* ningún actor de juego, más bien es un proxy conocido para los colisionables
* sin que tengan que conocer detalles del jugador y demás.
*/

namespace App_Interfaces
{

class Espaciable;

class Efecto_colision_recogedor_I
{
	///////////
	//Interface pública
	public:

							~Efecto_colision_recogedor_I();
	virtual const App_Interfaces::Espaciable&	obtener_espaciable()const=0;
	virtual bool					puede_recoger_salud()=0;
	virtual void					sumar_tiempo(float)=0;
	virtual void					sumar_salud(float)=0;
	virtual void					recibir_impacto(float)=0;
	virtual bool					es_jugador_aterrizado() const=0;
	virtual void					marcar_como_salida_nivel()=0;
	virtual bool					es_salida_nivel() const=0;
};
}

#endif
