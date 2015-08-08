#ifndef ENEMIGO_BASICO_H
#define ENEMIGO_BASICO_H

#include "../../definiciones/definiciones.h"
#include "../actor.h"
#include "../../recursos.h"
#include "../../interfaces/objeto_juego_i.h"
#include "../../interfaces/representable_i.h"
#include "../../interfaces/con_turno_i.h"
#include "../../graficos/bloque_transformacion_representable.h"

namespace App_Juego_ObjetoJuego
{

class Enemigo_basico:
		public App_Juego::Actor, 
		public App_Interfaces::Objeto_juego_I,
		public App_Interfaces::Representable_I,
		public App_Interfaces::Con_turno_I
{
	////////////////////////////
	// Interface pública.
	public:

							Enemigo_basico(float px, float py, float s=SALUD_DEFECTO);				

	////////////////////////////
	//Implementación de Objeto_juego_I
	public:

	virtual void 					recibir_visitante(App_Visitantes::Visitante_objeto_juego& v) {v.visitar(*this);}
	virtual void 					recibir_visitante(App_Visitantes::Visitante_objeto_juego_const& v)const {v.visitar(*this);}

	///////////////
	// Implementación de Representable_i.
	public:

	virtual unsigned short int obtener_profundidad_ordenacion()const;
	virtual void transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;

	///////////////
	//Implementación de Con_turno_I

	virtual void turno(float);

	////////////////////////////
	// Definiciones privadas.
	private:

	static const int 				W=20;
	static const int 				H=20;
	static const float				SALUD_DEFECTO;
	static const float				TIEMPO_PROXIMO_DISPARO_DEFECTO;

	////////////////////////////
	// Propiedades.
	private:

	float salud;
	float tiempo_proximo_disparo;
	App_Definiciones::direcciones direccion;
};

}

#endif
