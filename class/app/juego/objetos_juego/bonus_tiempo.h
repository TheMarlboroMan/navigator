#ifndef BONUS_TIEMPO_H
#define BONUS_TIEMPO_H

#include "../actor.h"
#include "../../recursos.h"
#include "../../interfaces/objeto_juego_i.h"
#include "../../interfaces/representable_i.h"
#include "../../graficos/bloque_transformacion_representable.h"
#include "../../interfaces/sonoro_i.h"
#include "../../audio/audio_reproducir.h"
#include "../../interfaces/generador_objetos_juego_i.h"
#include "../../interfaces/efecto_colision_i.h"

namespace App_Juego_ObjetoJuego
{

class Bonus_tiempo:
		public App_Juego::Actor, 
		public App_Interfaces::Representable_I,
		public App_Interfaces::Efecto_colision_I,
		public App_Interfaces::Sonoro_I,
		public App_Interfaces::Generador_objetos_juego_I
{
	////////////////
	// Interface pública:
	public:
							Bonus_tiempo(float x, float y, float t=CANTIDAD_TIEMPO_DEFECTO);

	float						acc_tiempo() const {return tiempo;}
	void						mut_tiempo(float v) {tiempo=v;}

	///////////////
	//Implementación de Generador_objetos_juego_I
	virtual	void					generar_objetos(App_Interfaces::Factoria_objetos_juego_I&);

	///////////////
	// Implementación de Efecto_colision_I...
	public:

	virtual void					efecto_colision(App_Interfaces::Efecto_colision_recogedor_I&);
	virtual bool					es_colision_para(const App_Interfaces::Espaciable& e)const {return en_colision_con(e);}

	////////////////
	// Implementación de Sonoro_i
	virtual bool					es_sonoro_borrar() const {return es_borrar();}

	///////////////
	// Implementación de Representable_i.
	public:

	virtual unsigned int	 			obtener_ciclos_representable()const;
	virtual unsigned short int 			obtener_profundidad_ordenacion()const;
	virtual void 					transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;
	virtual bool					es_representable_borrar() const {return es_borrar();}

	///////////////
	// Propiedades y definiciones.
	private:
	static const int 				W=16;
	static const int 				H=16;
	static const float				CANTIDAD_TIEMPO_DEFECTO;
	float						tiempo;	
};

}

#endif
