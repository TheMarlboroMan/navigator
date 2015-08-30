#ifndef PROYECTIL_BASE_H
#define PROYECTIL_BASE_H

#include "../actor_movil.h"
#include "../../interfaces/objeto_juego_i.h"
#include "../../interfaces/representable_i.h"
#include "../../interfaces/con_turno_i.h"
#include "../../interfaces/sonoro_i.h"
#include "../../interfaces/generador_objetos_juego_i.h"

/**
* La base para todos los proyectiles del juego.
*/ 

namespace App_Juego_ObjetoJuego
{

class Proyectil_base:
	public App_Juego::Actor_movil, 
	public App_Interfaces::Representable_I,
	public App_Interfaces::Con_turno_I,
	public App_Interfaces::Sonoro_I,
		//La base extiende esto porque el vector de proyectiles es de tipo base.
	public App_Interfaces::Generador_objetos_juego_I
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

	virtual void					colisionar_con_nivel()=0;
	virtual void					colisionar_con_enemigo()=0;
	virtual void					colisionar_con_jugador()=0;

	///////////////
	// Implementación de Con_turno_I
	public:

	virtual void 					turno(App_Interfaces::Contexto_turno_I&)=0;

	////////////////
	// Implementación de Generador_objetos_juego_I
	virtual	void					generar_objetos(App_Interfaces::Factoria_objetos_juego_I&)=0;

	///////////////
	// Implementación de Sonoro_I
	public:

	virtual bool 					es_sonoro_borrar() const {return es_borrar();}

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
