#include <stdexcept>
#include "bootstrap_aplicacion.h"
#include "../class/controladores/controlador_juego.h"
#include "../class/controladores/controlador_pausa.h"
#include "../class/app/graficos/animaciones.h"
#include "../class/app/generador/motor_mapas.h"
#include "../class/app/recursos.h"

using namespace App;

App::parametros_test App::obtener_parametros_test(DLibH::Controlador_argumentos& CARG)
{
	try
	{	
		auto p=DLibH::Herramientas::explotar(CARG.valor_argumento("test"), '.');
		
		//En caso de que esté malformada la cadena, se coge esto en "loop aplicacion", causando el fin del programa.
		if(p.size()!=3) throw std::runtime_error("El argumento 'test' está malformado, debe tener la forma test=1.2.3");

		int tipo=std::atoi(p[0].c_str());
		int nivel=std::atoi(p[1].c_str());
		int variante=std::atoi(p[2].c_str()); 

		parametros_test res;
		res.valido=true;
		res.tipo=tipo;
		res.nivel=nivel;
		res.variante=variante;
		return res;
	}
	catch(Controlador_argumentos_exception &e)
	{
		return App::parametros_test();
	}
}

void App::loop_aplicacion(Kernel_app& kernel)
{
	Audio::reproducir_musica(
		DLibA::Gestor_recursos_audio::obtener_musica(App::Recursos_audio::rm_blind_shift));

	//Declaraciones de herramientas externas.
	Director_estados DI;



	try
	{
		//Iniciar los recursos de animaciones...
		App_Graficos::Animaciones animaciones;
		animaciones.cargar();

		//TODO: Iniciar los recursos de actores genéricos...

		//Iniciar el motor de mapas y el primer nivel.
		const auto& params_test=App::obtener_parametros_test(kernel.acc_controlador_argumentos());

		//TODO: Contendría el parser de salas, que debe contener el diccionario de 
		//actores genéricos, que habría que inicializar antes.
		App_Generador::Motor_mapas MS;
		MS.iniciar_repo();

		if(params_test.valido)
		{
			MS.generar_mapa_test(params_test.tipo, params_test.nivel, params_test.variante);
		}
		else
		{
			MS.generar_mapa(10, 10);
		}

		//Controladores.
		Controlador_juego C_J(DI, MS.acc_mapa(), MS.acc_automapa(), animaciones);
		Controlador_pausa C_P(DI, MS.acc_automapa(), animaciones);

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
	catch(std::exception& e)
	{
		std::cout<<"ERROR: "<<e.what()<<std::endl;
		return;
	}
}
