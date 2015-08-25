#ifndef LOGICA_GENERADOR_PARTICULAS_H
#define LOGICA_GENERADOR_PARTICULAS_H

#include <vector>
#include <memory>

#include "particulas/definicion_particula.h"
#include "objetos_juego/particula_base.h"
#include "../interfaces/generador_particulas_i.h"

namespace App_Juego
{

class Logica_generador_particulas
{
	////////////////////////
	//Interface pública.
	public:
	typedef std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Particula_base> > Vsptr_Particula_base;
	typedef std::vector<std::shared_ptr<App_Interfaces::Generador_particulas_I>> Vsptr_Generador_particulas_I;

							Logica_generador_particulas(Vsptr_Particula_base&, App_Interfaces::Generador_particulas_I& j);
	virtual void 					procesar(Vsptr_Generador_particulas_I&);

	/////////////////////////
	//Propiedades privadas.
	private:

	Vsptr_Particula_base& 				particulas_controlador;
	App_Interfaces::Generador_particulas_I& 	jugador;
};
}

#endif
