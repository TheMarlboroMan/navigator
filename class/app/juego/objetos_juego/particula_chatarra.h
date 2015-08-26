#ifndef PARTICULA_CHATARRA_H
#define PARTICULA_CHATARRA_H

#include <herramientas/vector_2d/vector_2d.h>

#include "particula_movil_base.h"
#include "../../definiciones/sprites_particulas.h"
#include "../../recursos.h"
#include "../../../herramientas_proyecto/generador_numeros.h"

namespace App_Juego_ObjetoJuego
{
class Particula_chatarra:
	public Particula_movil_base
{
	//////////////////
	//Interface pública...
	public:
						Particula_chatarra(float x, float y, float tv, const DLibH::Vector_2d& v);

	//////////////
	// Implementación de Representable_I
	public:

	virtual unsigned short int 		obtener_profundidad_ordenacion()const;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;

	//////////////
	// Implementación de Con_turno_I
	public:

	virtual void				recibir_visitante(App_Visitantes::Visitante_con_turno& v) {v.visitar(*this);}

	/////////////////
	//Internas.
	private:

	static const int 				W=8;
	static const int				H=8;
	int						frame;
};
}

#endif
