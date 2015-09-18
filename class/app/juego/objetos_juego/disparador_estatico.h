#ifndef DISPARADOR_ESTATICO_H
#define DISPARADOR_ESTATICO_H

/**
* El disparador estático es un actor que no aparece en el mapa, no es 
* colisionable y su única forma de actuar con el mundo es crear proyectiles.
*/

#include "../../definiciones/definiciones.h"
#include "../actor.h"
#include "../../recursos.h"	//Necesitamos recursos de audio.
#include "../../interfaces/objeto_juego_i.h"
#include "../../interfaces/sonoro_i.h"
#include "../../interfaces/con_turno_i.h"
#include "../../interfaces/generador_objetos_juego_i.h"


namespace App_Juego_ObjetoJuego
{

class Disparador_estatico:
		public App_Juego::Actor, 
		public App_Interfaces::Sonoro_I,
		public App_Interfaces::Con_turno_I,
		public App_Interfaces::Generador_objetos_juego_I
{
	/////////////////////////////
	//Interface pública...
	public:
						Disparador_estatico(float x, float y, float t, float p, float d, App_Definiciones::direcciones dir, int longitud);

	///////////////
	// Implementación de Sonoro_I.
	public:

	virtual bool				es_sonoro_borrar() const {return es_borrar();}

	///////////////
	//Implementación de Con_turno_I
	public:

	virtual void 				turno(App_Interfaces::Contexto_turno_I&);

	///////////////
	//Implementación de Generador_objetos_juego_I
	public:

	virtual	void				generar_objetos(App_Interfaces::Factoria_objetos_juego_I&);

	////////////////////////////
	// Internas...

	private:

	App_Definiciones::direcciones		direccion;
	float 					tiempo_base;
	float					tiempo_actual;
	float					pausa_inicial;
	float					duracion_disparo;
	int					longitud;
};

}

#endif
