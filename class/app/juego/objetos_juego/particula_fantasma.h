#ifndef PARTICULA_FANTASMA_H
#define PARTICULA_FANTASMA_H

#include "particula_base.h"
#include "../../graficos/bloque_transformacion_representable.h"
#include "../../definiciones/definiciones.h"
#include <herramientas/caja/caja.h>

namespace App_Juego_ObjetoJuego
{
class Particula_fantasma:
	public Particula_base
{
	//////////////////////
	//Interface pública.
	public:
						Particula_fantasma(float x, float y, float tv, float ve, App_Definiciones::direcciones direccion, int recurso, const DLibH::Caja<int, int>& recorte);

	//////////////
	// Implementación de Representable_I
	public:

	virtual unsigned short int 		obtener_profundidad_ordenacion()const;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;
	virtual bool				es_representable_borrar()const {return es_borrar();}

	//////////////
	// Implementación de Con_turno_I
	public:

	virtual void 				turno(App_Interfaces::Contexto_turno_I&);
	virtual void				recibir_visitante(App_Visitantes::Visitante_con_turno& v) {v.visitar(*this);}

	/////////////////
	//Internas.
	private:

	float					x, y, w, h;
	float 					velocidad_expansion;
	App_Definiciones::direcciones 		direccion;
	int recurso;
	DLibH::Caja<int, int>			recorte;
};

}

#endif
