#ifndef PROYECTIL_RAYO_ESTATICO_H
#define PROYECTIL_RAYO_ESTATICO_H

#include <generador_numeros.h>
#include "proyectil_base.h"
#include "../../graficos/bloque_transformacion_representable.h"

/**
* Un proyectil estático, que ocupa siempre el mismo espacio en una caja y 
* que no desaparece al chocar con cosas.
**/

namespace App_Juego_ObjetoJuego
{
class Proyectil_rayo_estatico:
	public Proyectil_base
{
	/////////////////////
	//Interface pública.
	public:
							Proyectil_rayo_estatico(float x, float y, int w, int h, float potencia);

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

	virtual unsigned int 				obtener_ciclos_representable()const;
	virtual unsigned short int 			obtener_profundidad_ordenacion()const;
	virtual void 					transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;

	/////////////////////
	//Implementación de Actor_movil, tan inútil como parece porque no se mueve. Al menos de momento.
	public:
	virtual float 					obtener_peso() const {return 0.0f;}
	virtual float 					obtener_max_velocidad_caida() const {return 0.0f;}
	virtual void 					callback_ajuste(float pos, Actor_movil::posiciones_ajuste tipo) {}

	/////////////////////
	//Propiedades
	private:
	
	static const int				puntos_por_longitud=4;
	int						longitud;
	float 						tiempo_vida;
};
}

#endif
