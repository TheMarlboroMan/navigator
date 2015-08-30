#ifndef PARTICULA_EXPLOSION_H
#define PARTICULA_EXPLOSION_H

#include <herramientas/vector_2d/vector_2d.h>

#include "particula_movil_base.h"
#include "../../definiciones/sprites_particulas.h"
#include "../../recursos.h"

namespace App_Juego_ObjetoJuego
{
class Particula_explosion:
	public Particula_movil_base
{
	//////////////////
	//Interface pública...
	public:
						Particula_explosion(float x, float y, float tv, const DLibH::Vector_2d& v);

	//////////////
	// Implementación de Representable_I
	public:

	virtual unsigned short int 		obtener_profundidad_ordenacion()const;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;

	//////////////
	// Implementación de Con_turno_I
	public:

	virtual void 				turno(App_Interfaces::Contexto_turno_I&);
	virtual void				recibir_visitante(App_Visitantes::Visitante_con_turno& v) {v.visitar(*this);}

	/////////////////
	//Internas.
	private:

	int						frame_actual;
	mutable float						w, h;

};
}

#endif
