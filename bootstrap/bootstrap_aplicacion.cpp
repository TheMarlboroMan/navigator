
#include <stdexcept>
#include "bootstrap_aplicacion.h"
#include "../class/controladores/controlador_juego.h"

using namespace App;

void App::loop_aplicacion(Kernel_app& kernel)
{
	//Declaraciones de herramientas externas.
	Director_estados DI;

	App_RepositorioSalas::Repositorio_salas repo;

	try
	{
		repo.iniciar("data/salas/repo.dat");
	}
	catch(std::runtime_error& e)
	{
		std::cout<<"ERROR: "<<e.what()<<std::endl;
		return;
	}
	

	//Controladores e interfaces.
	Controlador_juego C_J(DI, kernel.acc_pantalla(), repo);

	Interface_controlador * IC=&C_J;

	//Loop principal.
	while(kernel.loop(*IC))
	{
		if(DI.es_cambio_estado())
		{
/*
			switch(DI.acc_estado_actual())
			{
				case Director_estados::t_estados::JUEGO: break;
				case Director_estados::t_estados::GENERADOR: break;
			}
*/

/*
			switch(DI.acc_estado_deseado())
			{
				case Director_estados::t_estados::JUEGO: 
					IC=&C_J; 
				break;
				case Director_estados::t_estados::GENERADOR: IC=&C_G; break;

			}
*/

			DI.confirmar_cambio_estado();
		}
	};
}
