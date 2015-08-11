#ifndef BONUS_SALUD_H
#define BONUS_SALUD_H

#include "../actor.h"
#include "../../recursos.h"
#include "../../graficos/bloque_transformacion_representable.h"
#include "../../interfaces/objeto_juego_i.h"
#include "../../interfaces/representable_i.h"
#include "../../interfaces/bonus_i.h"

namespace App_Juego_ObjetoJuego
{

class Bonus_salud:
		public App_Juego::Actor, 
		public App_Interfaces::Representable_I,
		public App_Interfaces::Bonus_I
{
	////////////////
	// Interface pública:
	public:
							Bonus_salud(float x, float y, float s=CANTIDAD_SALUD_DEFECTO);

	float						acc_salud() const {return salud;}
	void						mut_salud(float v) {salud=v;}

	///////////////
	// Implementación de Objeto_juego_i.
	public:

	virtual void 					recibir_visitante(App_Visitantes::Visitante_objeto_juego& v) {v.visitar(*this);}
	virtual void 					recibir_visitante(App_Visitantes::Visitante_objeto_juego_const& v)const {v.visitar(*this);}

	///////////////
	// Implementación de Bonus_i.
	public:

	virtual void 					recibir_visitante(App_Visitantes::Visitante_bonus& v) {v.visitar(*this);}
	bool						es_bonus_para(const Espaciable& e)const {return en_colision_con(e);}

	///////////////
	// Implementación de Representable_i.
	public:

	virtual unsigned short int 			obtener_profundidad_ordenacion()const;
	virtual void 					transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;
	virtual bool					es_representable_borrar() const {return es_borrar();}

	///////////////
	// Propiedades y definiciones.
	private:
	static const int 				W=16;
	static const int 				H=16;
	static const float				CANTIDAD_SALUD_DEFECTO;
	float						salud;

	////////////////
	// Métodos privados:
	private:
	
};

}

#endif
