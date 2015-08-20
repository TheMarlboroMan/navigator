#ifndef MOTOR_MAPAS_H
#define MOTOR_MAPAS_H

/**
* Esta clase envuelve la funcionalidad de los mapas para que sea la única 
* responsable de servirlos y generarlos.
*/

#include "traductor_mapas.h"
#include "generador_estructura_niveles.h"
#include "../repositorio_salas/repositorio_salas.h"

namespace App_Generador
{

class Motor_mapas
{
	////////////////
	//Interface pública.
	public:

						Motor_mapas();

	void					iniciar_repo();
	void					generar_mapa(int principales, int secundarias);
	App_Niveles::Mapa&			acc_mapa() {return mapa;}

	////////////////
	//Internas
	private:

	App_Niveles::Mapa			mapa;
	App_RepositorioSalas::Repositorio_salas	repo;
};

}

#endif

