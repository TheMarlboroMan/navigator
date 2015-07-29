#ifndef CELDA_H
#define CELDA_H

#include "../interfaces/espaciable.h"
#include "../graficos/representable.h"
#include "../recursos.h"

namespace App_Niveles
{

class Celda:public App_Interfaces::Espaciable, public App_Graficos::Representable
{
	//////////
	//Definiciones...
	public:

	enum class tipo_celda {solida};
	typedef unsigned int t_dim;
	static const t_dim DIM_CELDA=32;

	//////////
	// Propiedades
	private:

	t_dim x, y;
	tipo_celda tipo;

	///////////
	// Interface pública

	public:
	Celda(t_dim px, t_dim py, tipo_celda pt)
		:x(px), y(py), tipo(pt)
	{}

	//////////////////////////////
	//Implementación de Representable.
	public:
	virtual unsigned short int obtener_profundidad_ordenacion()const {return 0;}
	virtual void transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
	{
		b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::TR_BITMAP);
		b.establecer_recurso(App::Recursos_graficos::RT_DEFECTO);
		b.establecer_posicion(x*DIM_CELDA, y*DIM_CELDA, DIM_CELDA, DIM_CELDA);
		b.establecer_recorte(0, 0, DIM_CELDA, DIM_CELDA);
	}

	//////////////////////////////
	//Implementación de Espaciable
	public:
	virtual Espaciable::t_caja copia_caja() const {return Espaciable::t_caja(DIM_CELDA*x,DIM_CELDA*y,DIM_CELDA,DIM_CELDA);}

	//Ninguna de estas funciones hace nada porque la celda es inamovible.
	virtual void mut_x_caja(float) {}
	virtual void mut_y_caja(float) {}
	virtual void desplazar_caja(float, float) {}
	virtual void mut_w_caja(unsigned int) {}
	virtual void mut_h_caja(unsigned int) {}

};

}

#endif
