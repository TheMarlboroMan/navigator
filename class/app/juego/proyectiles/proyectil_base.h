#ifndef PROYECTIL_BASE_H
#define PROYECTIL_BASE_H

#include "../actor_movil.h"
#include "../../graficos/representable.h"
#include "../../interfaces/borrable_i.h"

/**
* La base para todos los proyectiles del juego.
* Implementa el método "turno", que probablemente vaya a ir en otra interface.
* Además es "borrable".
*/ 

namespace App_Juego_Proyectiles
{

class Proyectil_base:public App_Juego::Actor_movil, public App_Graficos::Representable, public App_Interfaces::Borrable_I
{
	/////////////////////
	//Interface pública.
	public:
					Proyectil_base(float x, float y, unsigned int w, unsigned int h);
	virtual				~Proyectil_base() {}
	float 				acc_potencia() const {return potencia;}
	void 				mut_potencia(float v) {potencia=v;}
	virtual	void			turno(float delta)=0;
	void				establecer_vector(const DLibH::Vector_2d& v);

	/////////////////////
	//Implementación de Representable.
	public:

	virtual unsigned short int 	obtener_profundidad_ordenacion()const=0;
	virtual void 			transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const=0;

	/////////////////////
	//Implementación de Actor_movil
	public:
	virtual float 			obtener_peso() const=0;
	virtual float 			obtener_max_velocidad_caida() const=0;
	virtual void 			callback_ajuste(float pos, posiciones_ajuste tipo)=0;

	/////////////////////
	//Propiedades
	private:
	float 				potencia;
};

}

#endif
