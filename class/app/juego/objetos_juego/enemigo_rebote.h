#ifndef ENEMIGO_REBOTE_H
#define ENEMIGO_REBOTE_H

#include "../actor_movil.h"
#include "../../definiciones/definiciones.h"
#include "../../interfaces/colisionable_i.h"
#include "../../interfaces/disparable_i.h"
#include "../../interfaces/con_turno_i.h"
#include "../../interfaces/representable_i.h"

namespace App_Juego_ObjetoJuego
{

class Enemigo_rebote:
	public App_Juego::Actor_movil,
	public App_Interfaces::Colisionable_I,
	public App_Interfaces::Disparable_I,
	public App_Interfaces::Con_turno_I,
	public App_Interfaces::Representable_I
	
{
	///////////////////////
	//Interface pública...
	public:

	enum class tipos_rebote {invertir, derecha, izquierda};
					Enemigo_rebote(float px, float py, float vel, tipos_rebote treb, App_Definiciones::direcciones dir);
	void				cambiar_direccion();

	///////////////////////
	//Implementación de Objeto_Juego_I vía otras interfaces.
	public:

	virtual void 			recibir_visitante(App_Visitantes::Visitante_objeto_juego& v) {v.visitar(*this);}
	virtual void 			recibir_visitante(App_Visitantes::Visitante_objeto_juego_const& v)const {v.visitar(*this);}


	///////////////////////
	//Implementación de Colisionable_I
	public:

	virtual void 			recibir_visitante(App_Visitantes::Visitante_colisionable& v) {v.visitar(*this);}
	virtual bool			es_colision_para(const Espaciable& e)const {return en_colision_con(e);}

	////////////////////////
	//Implementación de Disparable_I
	public:

	virtual void 			recibir_visitante(App_Visitantes::Visitante_disparable& v) {v.visitar(*this);}
	virtual void 			recibir_disparo(float potencia);
	virtual bool			es_colision_proyectil(const Espaciable& e)const {return en_colision_con(e);}

	////////////////////////
	//Implementación de Con_turno_I
	public:
	
	virtual void 			turno(float);
	virtual void			recibir_visitante(App_Visitantes::Visitante_con_turno& v) {v.visitar(*this);}

	/////////////////////////
	//Implementación de Representable_I.
	public:

	virtual unsigned short int 	obtener_profundidad_ordenacion()const;
	virtual void 			transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;
	virtual bool			es_representable_borrar()const {return es_borrar();}

	/////////////////
	//Implementación de Movil / Actor_Movil

	virtual float obtener_peso() const;
	virtual float obtener_max_velocidad_caida() const;
	virtual void callback_ajuste(float pos, posiciones_ajuste tipo);

	////////////////////////////
	//Propiedades...

	float				velocidad;
	tipos_rebote			rebote;
	float				tiempo;

	static const int 		W=16;
	static const int 		H=16;
};

}

#endif

