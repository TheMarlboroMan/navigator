#ifndef JUGADOR_H
#define JUGADOR_H

#include <memory>
#include "actor_movil.h"
#include "../graficos/representable.h"
#include "../recursos.h"
#include "../input/input_usuario.h"
//#include "../../herramientas_proyecto/tabla_sprites.h"
//#include "jugador_estados.h"

namespace App_Juego
{

class Jugador:public Actor_movil, public App_Graficos::Representable
{
	////////////////////////
	// Definiciones...

	public:

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


	/////////////////////////
	// Propiedades...

	private:

	App_Input::Input_usuario input;

	float salud;
	float escudo;

//	Tabla_sprites TREC;
//	t_direcciones direccion;

	/////////////////
	//Implementación de Movil/Actor_Movil

	virtual float obtener_peso() const {return 100.0;}
	virtual float obtener_max_velocidad_caida() const {return MAXIMA_VELOCIDAD_CAIDA;}
	virtual void callback_ajuste(float pos, Actor_movil::posiciones_ajuste tipo);

	///////////////////////
	// Implementación de Representable.

	public:

	virtual unsigned short int obtener_profundidad_ordenacion() const {return 20;}
	virtual void transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const;

	/////////////////////////
	// Métodos internos.
	
	private:

	void recibir_impacto(float val);

	////////////////////////
	// Interfaz pública...

	public:

	Jugador(float x=0.0, float y=0.0);
	~Jugador();

	void recoger_input(App_Input::Input_usuario iu) {input=iu;}
	void turno(float delta);

	void procesar_estado(float delta);

	int acc_salud() const {return salud;}
	int acc_escudo() const {return escudo;}

	void colocar_inicio()
	{
		mut_x_caja(32.0);
		mut_y_caja(32.0);
		establecer_vector(0.0, Movil::t_vector::V_X);
		establecer_vector(0.0, Movil::t_vector::V_Y);
	}

//	bool es_encarando_direccion(t_direcciones dir) const {return direccion==dir;}
};

}
#endif
