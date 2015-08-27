#include "logica_generador_particulas.h"

using namespace App_Juego;

Logica_generador_particulas::Logica_generador_particulas(Vsptr_Particula_base& v, Vsptr_Generador_particulas_I& g, App_Interfaces::Generador_particulas_I& j)
	:particulas_controlador(v), generadores(g), jugador(j)
{

}

void Logica_generador_particulas::procesar(Vsptr_Generador_particulas_I& v)
{
	auto f=[this](App_Interfaces::Generador_particulas_I& gp)
	{
		if(gp.hay_particulas())
		{
			auto vp=gp.acc_particulas();
			for(auto& p : vp) 
			{
				auto part=p->crear_particula();
				if(part.get()) particulas_controlador.push_back(part);
				else LOG<<"WARNING: Logica_generador_particulas detecta 'crear_particula' con resultado nullptr"<<std::endl;
			}
			gp.reset_particulas();
		}
	};
	for(auto& gp : generadores) f(*gp);
	for(auto& gp : v) f(*gp);
	f(jugador);
}
