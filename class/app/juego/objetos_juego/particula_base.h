#ifndef PARTICULA_BASE_H
#define PARTICULA_BASE_H

#include "../../interfaces/representable_i.h"
#include "../../interfaces/con_turno_i.h"

/**
* Clase base para la partícula...
* Al ser Representable_I y Con_turno_I tenemos claro que que podemos llamar a 
* todas esas funciones sin problema. Además, es implícitamente Objeto_juego
* mediante Con_turno_I de forma que es borrable.
* No tiene nada de información con respecto al "espacio" que ocupa: eso lo vamos
* a dejar para las clases que la deriven, ya sean "actor" o "actor_movil".
*/

namespace App_Juego_ObjetoJuego
{
class Particula_base:
	public App_Interfaces::Representable_I,
	public App_Interfaces::Con_turno_I
{
	//////////////
	//Interface pública:
	public:
						Particula_base(float tv);
	virtual					~Particula_base();

	//////////////
	// Implementación de Representable_I
	public:

	virtual unsigned short int 		obtener_profundidad_ordenacion()const=0;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const=0;
	virtual bool				es_representable_borrar()const=0;

	//////////////
	// Implementación de Con_turno_I
	public:

	virtual void 				turno(float)=0;
	virtual void				recibir_visitante(App_Visitantes::Visitante_con_turno& v)=0;

	/////////////
	//Privadas
	private:

	float					tiempo_vida;
};
}

#endif
