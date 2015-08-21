#include "motor_mapas.h"

using namespace App_Generador;

Motor_mapas::Motor_mapas()
	:mapa(0,0), automapa(5,5)
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

	struct llamable_salas
	{
		struct info
		{
			int x, y;
			App_Definiciones::direcciones dir;
			info(int px, int py, App_Definiciones::direcciones pd)
				:x(px), y(py), dir(pd)
			{} 
		};

		std::vector<info> v;

		void operator()(const App_Niveles::Sala& s)
		{
			v.push_back(info(s.acc_x(), s.acc_y(), s.acc_direcciones_entradas()) );
		}
	}ls;

	//Iniciar automapa y llenarlo de la información de mapa...
	automapa.inicializar(mapa.acc_w(), mapa.acc_h());
	mapa.para_cada_sala(ls);
	for(const auto& i : ls.v) automapa.configurar(i.x, i.y, i.dir);
}
