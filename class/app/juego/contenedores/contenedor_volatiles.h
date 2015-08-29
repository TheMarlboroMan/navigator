#ifndef CONTENEDOR_VOLATILES_H
#define CONTENEDOR_VOLATILES_H

#include <memory>
#include <vector>

#include "contenedor_herramientas.h"

#include "../objetos_juego/proyectil_base.h"
#include "../objetos_juego/particula_base.h"

namespace App_Juego_Contenedores
{

struct Contenedor_volatiles
{
	typedef std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base> sptr_Proyectil_base;
	typedef std::shared_ptr<App_Juego_ObjetoJuego::Particula_base> sptr_Particula_base;

	typedef std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base> > Vsptr_Proyectil_base;
	typedef std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Particula_base> > Vsptr_Particula_base;

	void						vaciar();
	void						fusionar_con(Contenedor_volatiles&);
	size_t						limpiar_para_borrar();

	Vsptr_Proyectil_base		 		proyectiles_jugador;
	Vsptr_Proyectil_base		 		proyectiles_enemigos;
	Vsptr_Particula_base				particulas;
};
}

#endif
