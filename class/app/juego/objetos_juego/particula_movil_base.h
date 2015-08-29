#ifndef PARTICULA_MOVIL_BASE_H
#define PARTICULA_MOVIL_BASE_H

#include <herramientas/vector_2d/vector_2d.h>

#include "particula_base.h"
#include "../actor_movil.h"

namespace App_Juego_ObjetoJuego
{
class Particula_movil_base:
	public Particula_base,
	public App_Juego::Actor_movil
{
	//////////////////
	//Interface pública...
	public:
						Particula_movil_base(float x, float y, float tv, const DLibH::Vector_2d& v);
						void mut_fuerza_frenado(float v) {fuerza_frenado=v;}
						float acc_fuerza_frenado() const {return fuerza_frenado;}
	//////////////
	// Implementación de Representable_I
	public:

	virtual unsigned short int 		obtener_profundidad_ordenacion()const=0;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const=0;

	virtual bool				es_representable_borrar()const {return es_borrar();}

	//////////////
	// Implementación de Con_turno_I
	public:

	virtual void 				turno(float);
	virtual void				recibir_visitante(App_Visitantes::Visitante_con_turno& v)=0;

	/////////////////
	//Implementación de Movil
	public:

	virtual float 				obtener_peso() const;
	virtual float 				obtener_max_velocidad_caida() const;
	virtual void 				callback_ajuste(float pos, posiciones_ajuste tipo);

	/////////////////
	//Internas.
	private:

	float					fuerza_frenado;
};
}

#endif