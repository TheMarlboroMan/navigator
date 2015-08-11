#ifndef PROYECTIL_BASE_H
#define PROYECTIL_BASE_H

#include "../actor_movil.h"
#include "../../interfaces/objeto_juego_i.h"
#include "../../interfaces/representable_i.h"
#include "../../interfaces/con_turno_i.h"

/**
* La base para todos los proyectiles del juego.
* Implementa el método "turno", que probablemente vaya a ir en otra interface.
* Además es "borrable".
*/ 

namespace App_Juego_ObjetoJuego
{

class Proyectil_base:
	public App_Juego::Actor_movil, 
	public App_Interfaces::Representable_I,
	public App_Interfaces::Con_turno_I
{
	/////////////////////
	//Interface pública.
	public:
							Proyectil_base(float x, float y, unsigned int w, unsigned int h);
	virtual						~Proyectil_base() {}
	float 						acc_potencia() const {return potencia;}
	float 						acc_potencia_original() const {return potencia_original;}
	void 						mut_potencia(float v);
	void						establecer_vector(const DLibH::Vector_2d& v);

	////////////////////////////
	//Implementación de Objeto_juego_I
	public:

	virtual void 					recibir_visitante(App_Visitantes::Visitante_objeto_juego& v)=0;
	virtual void 					recibir_visitante(App_Visitantes::Visitante_objeto_juego_const& v)const=0;

	///////////////
	// Implementación de Con_turno_I
	virtual void 					turno(float)=0;
	virtual void 					recibir_visitante(App_Visitantes::Visitante_con_turno& v)=0;

	///////////////
	// Implementación de Representable_i.
	public:

	virtual unsigned short int 			obtener_profundidad_ordenacion()const=0;
	virtual void 					transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const=0;
	virtual bool					es_representable_borrar()const{return es_borrar();}

	/////////////////////
	//Implementación de Actor_movil
	public:
	virtual float 					obtener_peso() const=0;
	virtual float 					obtener_max_velocidad_caida() const=0;
	virtual void 					callback_ajuste(float pos, posiciones_ajuste tipo)=0;

	/////////////////////
	//Propiedades
	private:
	float 						potencia;
	float						potencia_original;
};

}

#endif
