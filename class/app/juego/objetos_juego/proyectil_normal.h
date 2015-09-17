#ifndef PROYECTIL_NORMAL_H
#define PROYECTIL_NORMAL_H

#include <generador_numeros.h>
#include "proyectil_base.h"
#include "../../graficos/bloque_transformacion_representable.h"

/**
* Un proyectil corriente y moliente.
* Viene con varias clases helper para hacer constructores de acuerdo con 
* los tipos.
**/

namespace App_Juego_ObjetoJuego
{
class Proyectil_normal:
	public Proyectil_base
{
	/////////////////////
	//Definiciones:
	public:

	enum class colores {rojo, azul};

	/////////////////////
	//Interface pública.
	public:
							Proyectil_normal(float x, float y, int w, int h, const DLibH::Vector_2d& v, float potencia, App_Juego_ObjetoJuego::Proyectil_normal::colores color);
	virtual						~Proyectil_normal() {}
	void						mut_color(colores c) {color=c;}

	virtual void					colisionar_con_nivel();
	virtual void					colisionar_con_enemigo();
	virtual void					colisionar_con_jugador();

	////////////////
	// Implementación de Generador_objetos_juego_I
	virtual	void					generar_objetos(App_Interfaces::Factoria_objetos_juego_I&);


	///////////////
	// Implementación de Con_turno_I, por medio de Proyectil_base
	virtual void 					turno(App_Interfaces::Contexto_turno_I&);

	///////////////
	// Implementación de Representable_i.
	public:

	virtual unsigned short int 			obtener_profundidad_ordenacion()const;
	virtual void 					transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;

	/////////////////////
	//Implementación de Actor_movil
	public:
	virtual float 					obtener_peso() const {return 0.0f;}
	virtual float 					obtener_max_velocidad_caida() const {return 0.0f;}
	virtual void 					callback_ajuste(float pos, Actor_movil::posiciones_ajuste tipo) {}

	/////////////////////
	//Propiedades
	private:

	static const float 				FACTOR_DEBILITAR;
	 
	colores 					color;
	int						cantidad_chispas;
	float						tv_chispas;
};
}

#endif
