#ifndef CONTROLADOR_PAUSA_H
#define CONTROLADOR_PAUSA_H

#include "controlador_base.h"
#include "../app/niveles/mapa.h"

class Controlador_pausa:
	public Controlador_base
{
	//////////////////////
	//Interface pública...
	public:

						Controlador_pausa(Director_estados &DI, App_Niveles::Mapa&);

	virtual void 				preloop(Input_base& input, float delta);
	virtual void 				postloop(Input_base& input, float delta);
	virtual void 				loop(Input_base& input, float delta);
	virtual void 				dibujar(DLibV::Pantalla& pantalla);

	//////////////////////
	//Internas
	private:

	App_Niveles::Mapa&			mapa;
};

#endif
