#ifndef ENEMIGO_REBOTE_H
#define ENEMIGO_REBOTE_H

#include "../actor_movil.h"
#include "../../definiciones/definiciones.h"
#include "../../interfaces/efecto_colision_i.h"
#include "../../interfaces/disparable_i.h"
#include "../../interfaces/con_turno_i.h"
#include "../../interfaces/representable_i.h"

namespace App_Juego_ObjetoJuego
{

class Enemigo_rebote:
	public App_Juego::Actor_movil,
	public App_Interfaces::Efecto_colision_I,
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

	///////////////
	//Implementación de Efecto_colision_I
	public:

	virtual void		efecto_colision(App_Interfaces::Efecto_colision_recogedor_I&);
	virtual bool		es_colision_para(const App_Interfaces::Espaciable& e)const {return en_colision_con(e);}

	////////////////////////
	//Implementación de Disparable_I
	public:

	virtual void 			recibir_disparo(float potencia);
	virtual bool			es_colision_proyectil(const Espaciable& e)const {return en_colision_con(e);}

	////////////////////////
	//Implementación de Con_turno_I
	public:
	
					
	virtual void 			turno(App_Interfaces::Contexto_turno_I&);

	/////////////////////////
	//Implementación de Representable_I.
	public:

	virtual unsigned int 		obtener_ciclos_representable()const;
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

