
#include <stdexcept>
#include "bootstrap_aplicacion.h"
#include "../class/controladores/controlador_juego.h"
#include "../class/controladores/controlador_pausa.h"
#include "../class/app/generador/motor_mapas.h"
#include "../class/app/recursos.h"

using namespace App;

void App::loop_aplicacion(Kernel_app& kernel)
{
	Audio::reproducir_musica(
		DLibA::Gestor_recursos_audio::obtener_musica(App::Recursos_audio::rm_blind_shift));

	//Declaraciones de herramientas externas.
	Director_estados DI;

	//Iniciar el motor de mapas y el primer nivel.

	App_Generador::Motor_mapas MS;
	try
	{
		MS.iniciar_repo();
		MS.generar_mapa(10, 10);

		//Controladores.
		Controlador_juego C_J(DI, MS.acc_mapa(), MS.acc_automapa());
		Controlador_pausa C_P(DI, MS.acc_automapa());

		//Interface común...
		Interface_controlador * IC=&C_J;

		//Loop principal.
		while(kernel.loop(*IC))
		{
			if(DI.es_cambio_estado())
			{
				switch(DI.acc_estado_actual())
				{
					case Director_estados::t_estados::juego: break;
					case Director_estados::t_estados::pausa: break;
				}

				switch(DI.acc_estado_deseado())
				{
					case Director_estados::t_estados::juego: 
						IC=&C_J; 
					break;
					case Director_estados::t_estados::pausa: 
						C_P.refrescar();
						IC=&C_P; 
					break;

				}

				DI.confirmar_cambio_estado();
			}
		};

	}
	catch(std::runtime_error& e)
	{
		std::cout<<"ERROR: "<<e.what()<<std::endl;
		return;
	}
}
