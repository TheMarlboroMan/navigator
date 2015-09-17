#ifndef TRAZADOR_HUMO_H
#define TRAZADOR_HUMO_H

#include <generador_numeros.h>

#include "../../definiciones/definiciones.h"
#include "../actor_movil.h"
#include "../../recursos.h"
#include "../../interfaces/objeto_juego_i.h"
#include "../../interfaces/con_turno_i.h"
#include "../../interfaces/generador_objetos_juego_i.h"

/**
* El trazador de humo es un objeto no representable y móvil, cuya finalidad es
* ir creando partículas de humo allá por dónde pasa.
*/

namespace App_Juego_ObjetoJuego
{

class Trazador_humo:
		public App_Juego::Actor_movil, 
		public App_Interfaces::Con_turno_I,
		public App_Interfaces::Generador_objetos_juego_I
{
	/////////////////////
	//Interface pública.

	public:
				Trazador_humo(float x, float y, float tv, const DLibH::Vector_2d& v);
	
	/////////////////////
	//Implementación de Actor_movil

	public:

	virtual float 					obtener_peso() const;
	virtual float 					obtener_max_velocidad_caida() const;
	virtual void 					callback_ajuste(float pos, posiciones_ajuste tipo);

	///////////////
	//Implementación de Con_turno_I

	public:

	virtual void 					turno(App_Interfaces::Contexto_turno_I&);

	///////////////
	//Implementación de Generador_objetos_juego_I

	public:

	virtual	void					generar_objetos(App_Interfaces::Factoria_objetos_juego_I&);

	/////////////////////
	//Internas...

	private:

	static const float				max_tiempo_humo;
	static const float				duracion_humo;
	float						tiempo_vida;
	float						tiempo_humo;
};

}

#endif
