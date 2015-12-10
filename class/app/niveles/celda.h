#ifndef CELDA_H
#define CELDA_H

#include "../interfaces/espaciable.h"
#include "celda_base.h"

namespace App_Niveles
{

class Celda:
	public Celda_base,
	public App_Interfaces::Espaciable
{
	//////////
	//Definiciones...
	public:
	enum class tipo_celda {solida};

	///////////
	// Interface pública

	public:

						Celda(App_Definiciones::t_dim px, App_Definiciones::t_dim py, tipo_celda pt);

	//////////////////////////////
	//Implementación de Espaciable
	public:

	virtual Espaciable::t_caja 		copia_caja() const;

	//Ninguna de estas funciones hace nada porque la celda es inamovible.
	virtual void 				mut_x_caja(float) {}
	virtual void 				mut_y_caja(float) {}
	virtual void 				desplazar_caja(float, float) {}
	virtual void 				mut_w_caja(unsigned int) {}
	virtual void 				mut_h_caja(unsigned int) {}

	//////////
	// Propiedades
	private:

	tipo_celda 				tipo;
};

}

#endif
