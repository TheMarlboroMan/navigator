#include "logica_generador_particulas.h"

using namespace App_Juego;

Logica_generador_particulas::Logica_generador_particulas(Vsptr_Particula_base& v, App_Interfaces::Generador_particulas_I& j)
	:particulas_controlador(v), jugador(j)
{

}

void Logica_generador_particulas::procesar(Vsptr_Generador_particulas_I& v)
{
	auto f=[this](App_Interfaces::Generador_particulas_I& gp)
	{
		if(gp.hay_prototipos())
		{
			auto vp=gp.acc_prototipos();
			for(auto& p : vp) particulas_controlador.push_back(p->crear_particula());
			gp.reset_prototipos();
		}
	};

	f(jugador);
	for(auto& gp : v) f(*gp);
}
