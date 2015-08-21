#ifndef CONTROLADOR_PAUSA_H
#define CONTROLADOR_PAUSA_H

#include <tuple>
#include "controlador_base.h"
#include "../app/juego/automapa/vista_automapa.h"
#include "../app/juego/automapa/automapa.h"
#include "../app/graficos/representador.h"

class Controlador_pausa:
	public Controlador_base
{
	//////////////////////
	//Interface pública...
	public:

						Controlador_pausa(Director_estados &DI, App_Juego_Automapa::Automapa&);

	virtual void 				preloop(Input_base& input, float delta);
	virtual void 				postloop(Input_base& input, float delta);
	virtual void 				loop(Input_base& input, float delta);
	virtual void 				dibujar(DLibV::Pantalla& pantalla);

	void					centrar_mapa(const std::tuple<int, int>&);

	//////////////////////
	//Internas
	private:

	App_Graficos::Representador 		representador;
	App_Juego_Automapa::Automapa& 		automapa;
	App_Juego_Automapa::Vista_automapa	vista_automapa;

	int 					x_mapa, y_mapa;
};

#endif
