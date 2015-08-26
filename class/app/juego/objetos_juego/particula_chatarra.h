#ifndef PARTICULA_CHATARRA_H
#define PARTICULA_CHATARRA_H

#include <herramientas/vector_2d/vector_2d.h>

#include "particula_base.h"
#include "../actor_movil.h"
#include "../../../herramientas_proyecto/tabla_sprites.h"
#include "../../definiciones/sprites_particulas.h"
#include "../../recursos.h"
#include "../../../herramientas_proyecto/generador_numeros.h"

//TODO: Comparte casi todo con la partícula de explosión, de modo que las podemos
//unir en una "particula_movil" base.

namespace App_Juego_ObjetoJuego
{
class Particula_chatarra:
	public Particula_base,
	public App_Juego::Actor_movil
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
	virtual bool				es_representable_borrar()const {return es_borrar();}

	//////////////
	// Implementación de Con_turno_I
	public:

	virtual void 				turno(float);
	virtual void				recibir_visitante(App_Visitantes::Visitante_con_turno& v) {v.visitar(*this);}

	/////////////////
	//Implementación de Movil
	public:

	virtual float 				obtener_peso() const;
	virtual float 				obtener_max_velocidad_caida() const;
	virtual void 				callback_ajuste(float pos, posiciones_ajuste tipo);

	/////////////////
	//Internas.
	private:

	static const int 				W=8;
	static const int				H=8;
	int						frame;
};
}

#endif
