#ifndef CONTROLADOR_JUEGO
#define CONTROLADOR_JUEGO

#include <memory>
#include <tuple>

#include "controlador_base.h"
#include "../app/audio/gestor_audio.h"
#include "../app/juego/jugador.h"
#include "../app/juego/automapa/automapa.h"
#include "../app/juego/automapa/vista_automapa.h"
#include "../app/juego/sistemas/contador_tiempo.h"
#include "../app/juego/contenedores/contenedor_volatiles.h"

//TODO: Quitar...
#include "../app/juego/objetos_juego/proyectil_base.h"
#include "../app/juego/objetos_juego/proyectil_normal.h"
#include "../app/juego/objetos_juego/enemigo_basico.h"

#include "../app/niveles/mapa.h"
#include "../app/graficos/representador.h"
#include "../app/colisiones/calculador_colisiones.h"
#include "../app/input/recogedor_input.h"
#include "../app/lectores/info_obstaculos_genericos.h"

class Controlador_juego:public Controlador_base
{
	///////////////
	//Interface pública.
	public:
	
						Controlador_juego(Director_estados &DI, App_Niveles::Mapa&, App_Juego_Automapa::Automapa&, const App_Graficos::Animaciones&, const App_Lectores::Info_obstaculos_genericos&);
						~Controlador_juego();

	virtual void 				preloop(Input_base& input, float delta);
	virtual void 				postloop(Input_base& input, float delta);
	virtual void 				loop(Input_base& input, float delta);
	virtual void 				dibujar(DLibV::Pantalla& pantalla);
	virtual void				sonar(float);


	//////////////
	//Propiedades
	private:

	DLibV::Camara camara;

	App_Audio::Gestor_audio				gestor_audio;
	App_Graficos::Representador 			representador;
	App_Niveles::Mapa& 				mapa;
	App_Juego::Jugador 				jugador;

	App_Juego_Automapa::Automapa& 			automapa;
	App_Juego_Automapa::Vista_automapa		vista_automapa;
	const App_Lectores::Info_obstaculos_genericos&	info_obstaculos_genericos;
	App_Juego_Sistemas::Contador_tiempo 		contador_tiempo;
	App_Niveles::Sala * 				sala_actual;

	App_Juego_Contenedores::Contenedor_volatiles	contenedor_volatiles;
	
	bool						cambiar_modo_pantalla;
	int						cosa_audio;
	

	///////////////
	//Métodos internos.

	void					ajustar_camara_a_sala(const App_Niveles::Sala&);
	void					evaluar_enfoque_camara();
	void 					procesar_jugador(App_Juego::Jugador& j, float delta, App_Input::Input_usuario iu);
	bool 					controlar_y_efectuar_salida_sala(App_Juego::Jugador& j);
	void 					refrescar_automapa();
	void 					logica_mundo(float delta);
	void 					logica_proyectiles(float delta);
	void 					limpiar_pre_cambio_sala();
	void					cargar_sala(int ax, int ay, App_Definiciones::direcciones salida, App_Juego::Jugador& j, DLibH::Punto_2d<int> offset);
	void					limpiar_eliminados();
};

#endif
