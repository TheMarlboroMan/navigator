#ifndef PROYECTIL_NORMAL_H
#define PROYECTIL_NORMAL_H

#include "proyectil_base.h"

namespace App_Juego_Proyectiles
{
class Proyectil_normal:public Proyectil_base
{
	/////////////////////
	//Interface pública.
	public:
					Proyectil_normal(float x, float y, unsigned int w, unsigned int h);
	virtual				~Proyectil_normal() {}
	virtual	void			turno(float delta);

	/////////////////////
	//Implementación de Representable.
	public:
	virtual unsigned short int 	obtener_profundidad_ordenacion()const;
	virtual void 			transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;

	/////////////////////
	//Implementación de Actor_movil
	public:
	virtual float 			obtener_peso() const {return 0.0f;}
	virtual float 			obtener_max_velocidad_caida() const {return 0.0f;}
	virtual void 			callback_ajuste(float pos, Actor_movil::posiciones_ajuste tipo) {}

	/////////////////////
	//Propiedades
	private:
};
}

#endif
