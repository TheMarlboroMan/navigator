#ifndef PARTICULA_HUMO_H
#define PARTICULA_HUMO_H

#include "particula_base.h"
#include "../../definiciones/animaciones.h"
#include "../../recursos.h"

namespace App_Juego_ObjetoJuego
{

class Particula_humo:
	public Particula_base
{

	//////////////////
	//Interface pública...
	public:
						Particula_humo(float x, float y, float tv);

	//////////////
	// Implementación de Representable_I
	public:

	virtual unsigned int 			obtener_ciclos_representable()const;
	virtual unsigned short int 		obtener_profundidad_ordenacion()const;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;

	//////////////
	// Implementación de Con_turno_I
	public:

	virtual void 				turno(App_Interfaces::Contexto_turno_I&);

	/////////////////
	//Internas.
	private:

	//TODO: Porqué la partícula base no tiene ya una posición???. Si van a salir muchas más querremos revisar esto.
	float							x, y;
	mutable float						w, h;
};
}

#endif
