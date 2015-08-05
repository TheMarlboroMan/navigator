#ifndef BONUS_SALUD_H
#define BONUS_SALUD_H

#include "../actor.h"
#include "../../graficos/representable.h"
#include "../../recursos.h"
#include "../../interfaces/objeto_juego_i.h"
#include "../../interfaces/bonus_i.h"
#include "../../interfaces/borrable_i.h"

namespace App_Juego_ObjetoJuego
{

class Bonus_salud:
		public App_Juego::Actor, 
		public App_Interfaces::Objeto_juego_I, 
		public App_Graficos::Representable,
		public App_Interfaces::Borrable_I,
		public App_Interfaces::Bonus_I
{
	////////////////
	// Interface pública:
	public:
					Bonus_salud();
					Bonus_salud(float x, float y, float s=CANTIDAD_SALUD_DEFECTO);

	float				acc_salud() const {return salud;}
	void				mut_salud(float v) {salud=v;}

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
	// Implementación de Bonus_I.
	public:
	virtual void 			recibir_visitante(App_Visitantes::Visitante_bonus& v) {v.visitar(*this);}

	///////////////
	// Propiedades y definiciones.
	private:
	static const int 		W=16;
	static const int 		H=16;
	static const float		CANTIDAD_SALUD_DEFECTO;
	float				salud;

	////////////////
	// Métodos privados:
	private:
	
};

}

#endif
