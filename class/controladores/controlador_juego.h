#ifndef CONTROLADOR_JUEGO
#define CONTROLADOR_JUEGO

#include <sstream>
#include <memory>

#include "controlador_base.h"
#include "../app/juego/jugador.h"
#include "../app/juego/automapa/automapa.h"
#include "../app/juego/sistemas/contador_tiempo.h"
#include "../app/juego/objetos_juego/proyectil_base.h"
#include "../app/juego/objetos_juego/proyectil_normal.h"
#include "../app/juego/objetos_juego/enemigo_basico.h"
#include "../app/niveles/mapa.h"
#include "../app/graficos/representador.h"
#include "../app/colisiones/calculador_colisiones.h"
#include "../app/input/recogedor_input.h"

class Controlador_juego:public Controlador_base
{
	//////////////
	//Definiciones.
	public:
	typedef std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base> sptr_Proyectil_base;
	typedef std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base> > Vsptr_Proyectil_base;

	//////////////
	//Propiedades
	private:

	App_Graficos::Representador 		representador;
	App_Niveles::Mapa 			mapa;
	App_Juego::Jugador 			jugador;

	App_Juego_Automapa::Automapa 		automapa;
	App_Juego_Sistemas::Contador_tiempo 	contador_tiempo;
	App_Niveles::Sala * 			sala_actual;
	
	Vsptr_Proyectil_base		 	proyectiles_jugador;
	Vsptr_Proyectil_base		 	proyectiles_enemigos;

	///////////////
	//Métodos internos.

	void 					procesar_jugador(App_Juego::Jugador& j, float delta, App_Input::Input_usuario iu);
	bool 					controlar_y_efectuar_salida_sala(App_Juego::Jugador& j);
	void 					iniciar_automapa();
	void 					refrescar_automapa();
	void 					logica_mundo(float delta);
	void 					logica_proyectiles(float delta);
	void 					limpiar_pre_cambio_sala();
	void					cargar_sala(int ax, int ay, App_Definiciones::direcciones salida, App_Juego::Jugador& j);

	///////////////
	//Interface pública.
	public:
	
						Controlador_juego(Director_estados &DI, DLibV::Pantalla&);
						~Controlador_juego();

	virtual void 				preloop(Input_base& input, float delta);
	virtual void 				postloop(Input_base& input, float delta);
	virtual void 				loop(Input_base& input, float delta);
	virtual void 				dibujar(DLibV::Pantalla& pantalla);
};

#endif
