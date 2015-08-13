#ifndef ENTRADA_H
#define ENTRADA_H

#include "../../interfaces/espaciable.h"
#include "../../definiciones/definiciones.h"

//TODO: Pasar a objeto juego, con su propia interface si fuera necesario, "Conector_I".

namespace App_Juego_ObjetoJuego
{
class Entrada:public App_Interfaces::Espaciable
{
	///////////////////
	//Propiedades
	private:
	App_Definiciones::direcciones posicion;
	App_Definiciones::tipos::t_dim x, y;	

	//////////////////////////////
	//Implementación de Espaciable
	public:
	virtual Espaciable::t_caja copia_caja() const 
	{
		using namespace App_Definiciones;
		return Espaciable::t_caja(x, y,tipos::DIM_CELDA,tipos::DIM_CELDA);
	}

	//Ninguna de estas funciones hace nada porque la entrada es inamovible.
	virtual void mut_x_caja(float) {}
	virtual void mut_y_caja(float) {}
	virtual void desplazar_caja(float, float) {}
	virtual void mut_w_caja(unsigned int) {}
	virtual void mut_h_caja(unsigned int) {}

	///////////////////
	//Interface pública
	public:
	Entrada(App_Definiciones::direcciones p, App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py)
		:posicion(p), x(px), y(py)
	{}

	App_Definiciones::direcciones acc_posicion() const {return posicion;}
	App_Definiciones::tipos::t_dim acc_x() const {return x;}
	App_Definiciones::tipos::t_dim acc_y() const {return y;}
};
}

#endif
