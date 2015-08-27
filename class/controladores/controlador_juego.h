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
//TODO: Quitar...
#include "../app/juego/objetos_juego/proyectil_base.h"
#include "../app/juego/objetos_juego/proyectil_normal.h"
#include "../app/juego/objetos_juego/enemigo_basico.h"
#include "../app/niveles/mapa.h"
#include "../app/graficos/representador.h"
#include "../app/colisiones/calculador_colisiones.h"
#include "../app/input/recogedor_input.h"

class Controlador_juego:public Controlador_base
{
	///////////////
	//Interface pública.
	public:
	
						Controlador_juego(Director_estados &DI, App_Niveles::Mapa&, App_Juego_Automapa::Automapa&);
						~Controlador_juego();

	virtual void 				preloop(Input_base& input, float delta);
	virtual void 				postloop(Input_base& input, float delta);
	virtual void 				loop(Input_base& input, float delta);
	virtual void 				dibujar(DLibV::Pantalla& pantalla);
	virtual void				sonar(float);

	//////////////
	//Definiciones.
	public:
	typedef std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base> sptr_Proyectil_base;
	typedef std::shared_ptr<App_Juego_ObjetoJuego::Particula_base> sptr_Particula_base;

	typedef std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base> > Vsptr_Proyectil_base;
	typedef std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Particula_base> > Vsptr_Particula_base;

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
	App_Juego_Sistemas::Contador_tiempo 		contador_tiempo;
	App_Niveles::Sala * 				sala_actual;
	
	Vsptr_Proyectil_base		 		proyectiles_jugador;
	Vsptr_Proyectil_base		 		proyectiles_enemigos;
	Vsptr_Particula_base				particulas;

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
	void 					logica_particulas(float delta);
	void 					limpiar_pre_cambio_sala();
	void					cargar_sala(int ax, int ay, App_Definiciones::direcciones salida, App_Juego::Jugador& j, DLibH::Punto_2d<int> offset);
	void					limpiar_eliminados();
};

#endif
