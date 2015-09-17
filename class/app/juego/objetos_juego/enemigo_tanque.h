#ifndef ENEMIGO_TANQUE_H
#define ENEMIGO_TANQUE_H

#include <generador_numeros.h>

#include "../../definiciones/definiciones.h"
#include "../actor.h"
#include "../../recursos.h"
#include "../../interfaces/objeto_juego_i.h"
#include "../../interfaces/representable_i.h"
#include "../../interfaces/sonoro_i.h"
#include "../../interfaces/disparable_i.h"
#include "../../interfaces/con_turno_i.h"
#include "../../interfaces/efecto_colision_i.h"
#include "../../interfaces/generador_objetos_juego_i.h"
#include "../../graficos/bloque_transformacion_representable.h"

namespace App_Juego_ObjetoJuego
{

class Enemigo_tanque:
		public App_Juego::Actor, 
		public App_Interfaces::Representable_I,
		public App_Interfaces::Sonoro_I,
		public App_Interfaces::Con_turno_I,
		public App_Interfaces::Disparable_I,
		public App_Interfaces::Efecto_colision_I,
		public App_Interfaces::Generador_objetos_juego_I
{
	////////////////////////////
	// Interface pública.
	public:

							Enemigo_tanque(float px, float py, float s=SALUD_DEFECTO);

	///////////////
	// Implementación de Representable_i.
	public:

	virtual unsigned short int 			obtener_profundidad_ordenacion()const;
	virtual unsigned int 				obtener_ciclos_representable()const;
	virtual void 					transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;
	virtual bool					es_representable_borrar() const {return es_borrar();}

	///////////////
	// Implementación de Sonoro_I.
	public:

	virtual bool					es_sonoro_borrar() const {return es_borrar();}

	///////////////
	//Implementación de Con_turno_I
	public:

	virtual void 		turno(App_Interfaces::Contexto_turno_I&);

	///////////////
	//Implementación de Disparable_I
	public:

	virtual void 		recibir_disparo(float potencia);
	virtual bool		es_colision_proyectil(const Espaciable& e)const {return en_colision_con(e);}

	///////////////
	//Implementación de Generador_objetos_juego_I
	public:

	virtual	void		generar_objetos(App_Interfaces::Factoria_objetos_juego_I&);

	///////////////
	//Implementación de Efecto_colision_I
	public:

	virtual void		efecto_colision(App_Interfaces::Efecto_colision_recogedor_I&);
	virtual bool		es_colision_para(const App_Interfaces::Espaciable& e)const {return en_colision_con(e);}

	////////////////////////////
	// Definiciones privadas.
	private:

	static const int 				W=24;
	static const int 				H=9;
	static const float				SALUD_DEFECTO;
	static const float				TIEMPO_PROXIMO_DISPARO_DEFECTO;

	////////////////////////////
	// Propiedades.
	private:

	float 						salud;
	float 						tiempo_proximo_disparo;
	float						angulo;
};

}

#endif