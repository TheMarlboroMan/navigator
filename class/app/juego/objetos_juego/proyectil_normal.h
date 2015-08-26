#ifndef PROYECTIL_NORMAL_H
#define PROYECTIL_NORMAL_H

#include "proyectil_base.h"
#include "../../graficos/bloque_transformacion_representable.h"
#include "../../../herramientas_proyecto/generador_numeros.h"
#include "../particulas/definicion_particula_chispa.h"

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

	class Propiedades_proyectil
	{
		private:
		float x, y;
		unsigned int w, h;
		public:
		Propiedades_proyectil(float px, float py, unsigned int pw, unsigned int ph):x(px), y(py), w(pw), h(ph) {}
		friend class Proyectil_normal;
	};

	struct Propiedades_proyectil_jugador:public Propiedades_proyectil
	{
		public:
		static const unsigned int W=8, H=8;
		Propiedades_proyectil_jugador(float px, float py):Propiedades_proyectil(px, py, W, H) {}
	};

	/////////////////////
	//Interface pública.
	public:
							Proyectil_normal(const Propiedades_proyectil& pp);
	virtual						~Proyectil_normal() {}
	void						mut_color(colores c) {color=c;}

	virtual void					colisionar_con_nivel();
	virtual void					colisionar_con_enemigo();
	virtual void					colisionar_con_jugador();

	///////////////
	// Implementación de Con_turno_I, por medio de Proyectil_base
	virtual void 					turno(float);
	virtual void 					recibir_visitante(App_Visitantes::Visitante_con_turno& v) {v.visitar(*this);}

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

	void						generar_chispas(float, int);

	static const float FACTOR_DEBILITAR;
	 
	colores color;
};
}

#endif
