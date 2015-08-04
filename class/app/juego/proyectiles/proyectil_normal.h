#ifndef PROYECTIL_NORMAL_H
#define PROYECTIL_NORMAL_H

#include "proyectil_base.h"

/**
* Un proyectil corriente y moliente.
* Viene con varias clases helper para hacer constructores de acuerdo con 
* los tipos.
**/

namespace App_Juego_Proyectiles
{
class Proyectil_normal:public Proyectil_base
{
	/////////////////////
	//Definiciones:
	public:
	class Propiedades_proyectil
	{
		private:
		float x, y;
		unsigned int w, h;
		public:
		Propiedades_proyectil(float px, float py, unsigned int pw, unsigned int ph):x(px), y(py), w(pw), h(ph) {}
		friend class Proyectil_normal;
	};

	struct Propiedades_proyectil_jugador:public Propiedades_proyectil
	{
		public:
		static const unsigned int W=8, H=8;
		Propiedades_proyectil_jugador(float px, float py):Propiedades_proyectil(px, py, W, H) {}
	};

	/////////////////////
	//Interface pública.
	public:
//					Proyectil_normal(float x, float y, unsigned int w, unsigned int h);
					Proyectil_normal(const Propiedades_proyectil& pp);
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
