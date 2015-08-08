#ifndef CELDA_H
#define CELDA_H

#include "../interfaces/espaciable.h"
#include "../interfaces/representable_i.h"
#include "../graficos/representador.h"
#include "../recursos.h"
#include "../definiciones/definiciones.h"

namespace App_Niveles
{

class Celda:
	public App_Interfaces::Espaciable, 
	public App_Interfaces::Representable_I
{
	//////////
	//Definiciones...
	public:

	enum class tipo_celda {solida};

	//////////
	// Propiedades
	private:

	App_Definiciones::tipos::t_dim x, y;
	tipo_celda tipo;

	///////////
	// Interface pública

	public:

	/**
	* @param t_dim x
	* @param t_dim y
	* @param tipo_celda t
	*/

	Celda(App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py, tipo_celda pt)
		:x(px), y(py), tipo(pt)
	{}

	//////////////////////////////
	//Implementación de Representable_I.
	public:
	virtual unsigned short int obtener_profundidad_ordenacion()const {return 0;}
	virtual void transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
	{
		using namespace App_Definiciones;
		b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::TR_BITMAP);
		b.establecer_recurso(App::Recursos_graficos::RT_DEFECTO);
		b.establecer_posicion(x*tipos::DIM_CELDA, y*tipos::DIM_CELDA, tipos::DIM_CELDA, tipos::DIM_CELDA);
		b.establecer_recorte(0, 0, tipos::DIM_CELDA, tipos::DIM_CELDA);
	}

	//////////////////////////////
	//Implementación de Espaciable
	public:
	virtual Espaciable::t_caja copia_caja() const 
	{
		using namespace App_Definiciones;
		return Espaciable::t_caja(tipos::DIM_CELDA*x,tipos::DIM_CELDA*y,tipos::DIM_CELDA,tipos::DIM_CELDA);
	}

	//Ninguna de estas funciones hace nada porque la celda es inamovible.
	virtual void mut_x_caja(float) {}
	virtual void mut_y_caja(float) {}
	virtual void desplazar_caja(float, float) {}
	virtual void mut_w_caja(unsigned int) {}
	virtual void mut_h_caja(unsigned int) {}

};

}

#endif
