#ifndef CONTROLADOR_JUEGO
#define CONTROLADOR_JUEGO

#include <sstream>

#include "controlador_base.h"
#include "../app/juego/jugador.h"
#include "../app/niveles/mapa.h"
#include "../app/graficos/representador.h"
#include "../app/colisiones/calculador_colisiones.h"
#include "../app/input/recogedor_input.h"

class Controlador_juego:public Controlador_base
{
	//////////////
	//Propiedades
	private:

	App_Graficos::Representador representador;
	App_Niveles::Mapa mapa;
	App_Juego::Jugador jugador;

	App_Niveles::Sala * sala_actual;

	///////////////
	//Métodos internos.

	void procesar_jugador(App_Juego::Jugador& j, float delta, App_Input::Input_usuario iu);
	void controlar_salida_sala(App_Juego::Jugador& j);

	///////////////
	//Interface pública.
	public:
	
	Controlador_juego(Director_estados &DI, DLibV::Pantalla&);
	~Controlador_juego();

	virtual void preloop(Input_base& input, float delta);
	virtual void postloop(Input_base& input, float delta);
	virtual void loop(Input_base& input, float delta);
	virtual void dibujar(DLibV::Pantalla& pantalla);
};

#endif
