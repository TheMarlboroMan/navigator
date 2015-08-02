#ifndef BONUS_TIEMPO_H
#define BONUS_TIEMPO_H

#include "../actor.h"
#include "../../graficos/representable.h"
#include "../../recursos.h"
#include "../../interfaces/objeto_juego_i.h"

namespace App_Juego_ObjetoJuego
{

class Bonus_tiempo:
		public App_Juego::Actor, 
		public App_Interfaces::Objeto_juego_I, 
		public App_Graficos::Representable
{
	////////////////
	// Interface pública:
	public:
					Bonus_tiempo();
					Bonus_tiempo(float x, float y, float t=CANTIDAD_TIEMPO_DEFECTO);

	float				acc_tiempo() const {return tiempo;}
	void				mut_tiempo(float v) {tiempo=v;}

	///////////////
	// Implementación de Representable.
	public:
	virtual unsigned short int 	obtener_profundidad_ordenacion()const;
	virtual void 			transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;

	///////////////
	// Implementación de Objeto_juego_i.
	public:
	virtual void 			recibir_visitante(App_Visitantes::Visitante_objeto_juego& v) {v.visitar(*this);}
	virtual void 			recibir_visitante(App_Visitantes::Visitante_objeto_juego_const& v)const {v.visitar(*this);}

	///////////////
	// Propiedades y definiciones.
	private:
	static const int 		W=16;
	static const int 		H=16;
	static const float		CANTIDAD_TIEMPO_DEFECTO;
	float				tiempo;

	////////////////
	// Métodos privados:
	private:
	
};

}

#endif