#ifndef JUGADOR_H
#define JUGADOR_H

#include <memory>
#include <map>
#include <valor_limitado.h>
#include "actor_movil.h"
#include "../interfaces/representable_i.h"
#include "../interfaces/sonoro_i.h"
#include "../interfaces/generador_objetos_juego_i.h"
#include "../graficos/bloque_transformacion_representable.h"
#include "../recursos.h"
#include "../input/input_usuario.h"
#include "../definiciones/definiciones.h"

namespace App_Juego
{

class Jugador:
	public Actor_movil, 
	public App_Interfaces::Representable_I,	
	public App_Interfaces::Sonoro_I,
	public App_Interfaces::Generador_objetos_juego_I
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

	float 					acc_salud() const {return salud.actual();}
	float 					acc_escudo() const {return escudo.actual();}
	float 					acc_energia() const {return energia.actual();}
	App_Interfaces::Espaciable::t_caja	acc_posicion_anterior() const {return posicion_anterior;}
	bool					es_aterrizado() const;

	void					sumar_salud(float v);

	App_Definiciones::direcciones 		acc_direccion() const {return direccion;}
	bool 					es_encarando_direccion(App_Definiciones::direcciones dir) const {return direccion==dir;}
	bool					puede_recoger_salud() const {return salud < MAX_SALUD;}
	bool					disparar();
	void					contabilizar_tiempo_aterrizado(float v);
	void 					recibir_impacto(float val);
	

	/////////////////
	//Implementación de Movil/Actor_Movil
	public:

	virtual float 				obtener_peso() const {return 100.0;}
	virtual float 				obtener_max_velocidad_caida() const {return MAXIMA_VELOCIDAD_CAIDA;}
	virtual void 				callback_ajuste(float pos, Actor_movil::posiciones_ajuste tipo);

	///////////////////////
	// Implementación de Generador_objetos_juego_I

	virtual	void				generar_objetos(App_Interfaces::Factoria_objetos_juego_I&);

	///////////////////////
	// Implementación de Representable_I.
	public:

	virtual unsigned int			obtener_ciclos_representable()const;
	virtual unsigned short int 		obtener_profundidad_ordenacion() const;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const;
	virtual bool				es_representable_borrar() const {return false;}

	///////////////////////
	// Implementación de Sonoro_I.
	public:

	virtual bool				es_sonoro_borrar() const {return false;}

	/////////////////////////
	// Métodos internos.
	private:

	void					consumir_energia(float c);

	////////////////////////
	// Definiciones internas.
	private:

	static const int W=25;
	static const int H=14;

	static const float MAX_SALUD;
	static const float MAX_ESCUDO;
	static const float MAX_ENERGIA;
	static const float ESCUDO_RECUPERADO_POR_SEGUNDO;
	static const float ENERGIA_RECUPERADA_POR_SEGUNDO;
	static const float ENERGIA_ESTASIS_POR_SEGUNDO;
	static const float ACELERACION_VERTICAL_SEGUNDO;
	static const float ACELERACION_HORIZONTAL_SEGUNDO;
	static const float DECELERACION_HORIZONTAL_SEGUNDO;
	static const float MAXIMA_VELOCIDAD_HORIZONTAL;
	static const float MAXIMA_VELOCIDAD_VERTICAL;
	static const float MAXIMA_VELOCIDAD_CAIDA;
	static const float VELOCIDAD_MINIMA_IMPACTO;
	static const float TIEMPO_COOLOFF_ENERGIA;
	static const float UMBRAL_DETENCION_ESTASIS;
	static const float FACTOR_DETENCION_ESTASIS;
	static const float VALOR_GRAVEDAD;
	static const float TIEMPO_COMPLETAR_ATERRIZAJE;
	static const float VELOCIDAD_MOD_COLOR;

	/////////////////////////
	// Propiedades...
	private:

	typedef Herramientas_proyecto::Valor_limitado<float>	flim;

	struct {float r, g, b;}			mod_color;

	App_Input::Input_usuario 		input;
	App_Interfaces::Espaciable::t_caja			posicion_anterior;

	flim 					salud;
	flim					energia;
	flim 					escudo;
	float					cooloff_energia;
	float					tiempo_aterrizado;

	struct
	{ 
		bool				crear_fantasma=false;
		float				tiempo_dano=0.f;
		size_t				dano_recibido=0;
		size_t				salud_recuperada=0;
	}senales;

//	Tabla_sprites TREC;
	App_Definiciones::direcciones 		direccion;

};

}
#endif
