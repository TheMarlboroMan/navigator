#include "motor_mapas.h"

using namespace App_Generador;

Motor_mapas::Motor_mapas()
	:mapa(0,0)
{

}

/**
* @throw std::runtime_error
*/

void Motor_mapas::iniciar_repo()
{
	repo.iniciar("data/salas/repo.dat");
}

void Motor_mapas::generar_mapa(int principales, int secundarias)
{
	Generador_estructura_niveles GEN;
	GEN.generar_camino_principal(principales);
	GEN.generar_salas_secundarias(secundarias);
	GEN.normalizar();

	Traductor_mapas TM;
	mapa=TM.traducir_mapa(GEN.acc_proto_salas(), repo);
}
