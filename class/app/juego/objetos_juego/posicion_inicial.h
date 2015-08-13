#ifndef POSICION_INICIAL_H
#define POSICION_INICIAL_H

#include "../../interfaces/espaciable.h"
#include "../../definiciones/definiciones.h"

//TODO: Pasar a objeto juego, con su propia interface si fuera necesario.

namespace App_Juego_ObjetoJuego
{
class Posicion_inicial:
	public App_Interfaces::Espaciable
{
	///////////////////
	//Interface pública
	public:
						Posicion_inicial(App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py);
	App_Definiciones::tipos::t_dim 		acc_x() const {return x;}
	App_Definiciones::tipos::t_dim 		acc_y() const {return y;}

	//////////////////////////////
	//Implementación de Espaciable
	public:

	virtual Espaciable::t_caja 		copia_caja() const;

	//Ninguna de estas funciones hace nada porque es inamovible.
	virtual void 				mut_x_caja(float) {}
	virtual void 				mut_y_caja(float) {}
	virtual void 				desplazar_caja(float, float) {}
	virtual void 				mut_w_caja(unsigned int) {}
	virtual void 				mut_h_caja(unsigned int) {}

	///////////////////
	//Propiedades
	private:
	
	App_Definiciones::tipos::t_dim 		x, y;	
};
}

#endif
