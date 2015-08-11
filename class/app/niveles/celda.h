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

	///////////
	// Interface pública

	public:

						Celda(App_Definiciones::tipos::t_dim px, App_Definiciones::tipos::t_dim py, tipo_celda pt);


	//////////////////////////////
	//Implementación de Representable_I.
	public:

	virtual unsigned short int 		obtener_profundidad_ordenacion()const {return 0;}
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const;
	virtual bool				es_representable_borrar() const {return false;}

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

	App_Definiciones::tipos::t_dim 		x, y;
	tipo_celda 				tipo;
};

}

#endif
