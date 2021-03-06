#ifndef PARTICULA_EXPLOSION_H
#define PARTICULA_EXPLOSION_H

#include "particula_movil_base.h"
#include "../../definiciones/animaciones.h"
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

	virtual unsigned int	 		obtener_ciclos_representable()const;
	virtual unsigned short int 		obtener_profundidad_ordenacion()const;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;

	//////////////
	// Implementación de Con_turno_I
	public:

	virtual void 				turno(App_Interfaces::Contexto_turno_I&);

	/////////////////
	//Internas.
	private:

	mutable float						w, h;

};
}

#endif
