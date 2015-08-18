#ifndef CELDA_DECORATIVA_H
#define CELDA_DECORATIVA_H

#include "celda_base.h"
#include "../interfaces/representable_i.h"
#include "../definiciones/definiciones.h"
#include "../recursos.h"
#include "../../herramientas_proyecto/tabla_sprites.h"

namespace App_Niveles
{

class Celda_decorativa:
	public Celda_base,
	public App_Interfaces::Representable_I
{
	///////////
	// Interface pública

	public:

						Celda_decorativa(App_Definiciones::t_dim px, App_Definiciones::t_dim py, App_Definiciones::t_dim p_indice);

	//////////////////////////////
	//Implementación de Representable_I.
	public:

	virtual unsigned short int 		obtener_profundidad_ordenacion()const {return 0;}
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const;
	virtual bool				es_representable_borrar() const {return false;}

	//////////
	// Propiedades
	private:

	static HerramientasProyecto::Tabla_sprites tabla_sprites;

	App_Definiciones::t_dim	indice;

};

}

#endif