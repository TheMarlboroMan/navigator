#ifndef SALIDA_H
#define SALIDA_H

#include "../../interfaces/espaciable.h"
#include "../../interfaces/representable_i.h"
#include "../../interfaces/colisionable_i.h"
#include "../../definiciones/definiciones.h"
#include "../../graficos/bloque_transformacion_representable.h"
#include "../../recursos.h"

/**
* Salida del nivel.
*/

namespace App_Juego_ObjetoJuego
{
class Salida:
	public App_Interfaces::Espaciable,
	public App_Interfaces::Representable_I,
	public App_Interfaces::Colisionable_I
{
	///////////////////
	//Interface pública
	public:

						Salida(App_Definiciones::t_dim px, App_Definiciones::t_dim py);
	App_Definiciones::t_dim 		acc_x() const {return x;}
	App_Definiciones::t_dim 		acc_y() const {return y;}

	//////////////////////////////
	//Implementación de Espaciable
	public:

	virtual Espaciable::t_caja 		copia_caja() const;

	//Ninguna de estas funciones hace nada porque la entrada es inamovible.
	virtual void 				mut_x_caja(float) {}
	virtual void				mut_y_caja(float) {}
	virtual void 				desplazar_caja(float, float) {}
	virtual void 				mut_w_caja(unsigned int) {}
	virtual void 				mut_h_caja(unsigned int) {}	

	///////////////
	// Implementación de Representable_i.
	public:

	virtual unsigned short int 		obtener_profundidad_ordenacion()const;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;
	virtual bool				es_representable_borrar() const {return es_borrar();}

	///////////////
	//Implementación de Colisionable_I
	public:

	virtual void 				recibir_visitante(App_Visitantes::Visitante_colisionable& v) {v.visitar(*this);}
	virtual bool				es_colision_para(const Espaciable& e)const {return en_colision_con(e);}

	///////////////////
	//Propiedades
	private:

	static const App_Definiciones::t_dim	W=32;
	static const App_Definiciones::t_dim	H=32;
	App_Definiciones::t_dim 		x, y;
};
}

#endif
