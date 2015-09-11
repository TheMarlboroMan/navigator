#ifndef PARTICULA_BASE_H
#define PARTICULA_BASE_H

#include "../../interfaces/representable_i.h"
#include "../../interfaces/con_turno_i.h"
#include "../../../herramientas_proyecto/tabla_sprites.h"

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
	float					acc_tiempo_vida() const {return tiempo_vida;}
	float					acc_tiempo_vida_inicial() const {return tiempo_vida_inicial;}
	int					calcular_parcial_tiempo_vida(float t) const;
	void					restar_tiempo_vida(float v);
	bool					es_expirada() const {return tiempo_vida <= 0.0f;}
	float					acc_tiempo_activa() const {return tiempo_vida_inicial - tiempo_vida;}

	//////////////
	// Implementación de Representable_I
	public:

	virtual unsigned short int 		obtener_profundidad_ordenacion()const=0;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const=0;
	virtual bool				es_representable_borrar()const {return es_borrar();}

	//////////////
	// Implementación de Con_turno_I
	public:

	virtual void 				turno(App_Interfaces::Contexto_turno_I&)=0;

	/////////////
	//Privadas
	private:

	float					tiempo_vida;
	float					tiempo_vida_inicial;

};
}

#endif
