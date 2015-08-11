#ifndef JUGADOR_H
#define JUGADOR_H

#include <memory>
#include "actor_movil.h"
#include "../interfaces/representable_i.h"
#include "../graficos/bloque_transformacion_representable.h"
#include "../recursos.h"
#include "../input/input_usuario.h"
#include "../definiciones/definiciones.h"
//#include "../../herramientas_proyecto/tabla_sprites.h"
//#include "jugador_estados.h"

namespace App_Juego
{

class Jugador:
	public Actor_movil, 
	public App_Interfaces::Representable_I
{
	////////////////////////
	// Definiciones...
	public:

	////////////////////////
	// Interfaz pública...
	public:
						Jugador(float x=0.0, float y=0.0);
						~Jugador();

	void 					recoger_input(App_Input::Input_usuario iu) {input=iu;}
	void 					turno(float delta);

	void 					procesar_estado(float delta);

	int 					acc_salud() const {return salud;}
	int 					acc_escudo() const {return escudo;}
	App_Interfaces::Espaciable::t_caja	acc_posicion_anterior() const {return posicion_anterior;}

	void					sumar_salud(float v);

	App_Definiciones::direcciones 		acc_direccion() const {return direccion;}
	bool 					es_encarando_direccion(App_Definiciones::direcciones dir) const {return direccion==dir;}
	bool					puede_recoger_salud() const {return salud < MAX_SALUD;}
	void 					recibir_impacto(float val);
	

	/////////////////
	//Implementación de Movil/Actor_Movil
	public:

	virtual float 				obtener_peso() const {return 100.0;}
	virtual float 				obtener_max_velocidad_caida() const {return MAXIMA_VELOCIDAD_CAIDA;}
	virtual void 				callback_ajuste(float pos, Actor_movil::posiciones_ajuste tipo);

	///////////////////////
	// Implementación de Representable_I.
	public:

	virtual unsigned short int 		obtener_profundidad_ordenacion() const {return 20;}
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const;
	virtual bool				es_representable_borrar() const {return false;}

	/////////////////////////
	// Métodos internos.
	private:

	////////////////////////
	// Definiciones internas.
	private:

	static const int W=25;
	static const int H=14;

	static const int MAX_SALUD=100;
	static const int MAX_ESCUDO=100;
	static const int ESCUDO_RECUPERADO_POR_SEGUNDO=25;
	static const float ACELERACION_VERTICAL_SEGUNDO;
	static const float ACELERACION_HORIZONTAL_SEGUNDO;
	static const float DECELERACION_HORIZONTAL_SEGUNDO;
	static const float MAXIMA_VELOCIDAD_HORIZONTAL;
	static const float MAXIMA_VELOCIDAD_VERTICAL;
	static const float MAXIMA_VELOCIDAD_CAIDA;
	static const float VELOCIDAD_MINIMA_IMPACTO;
	static const float COOLOFF_RECUPERAR_ESCUDO;

	/////////////////////////
	// Propiedades...
	private:

	App_Input::Input_usuario 		input;
	App_Interfaces::Espaciable::t_caja			posicion_anterior;

	float 					salud;
	float 					escudo;
	float					cooloff_escudo;

//	Tabla_sprites TREC;
	App_Definiciones::direcciones 		direccion;

};

}
#endif
