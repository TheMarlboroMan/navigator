#ifndef CONTENEDOR_VOLATILES_H
#define CONTENEDOR_VOLATILES_H

#include <memory>
#include <vector>

#include "contenedor_herramientas.h"

#include "../objetos_juego/proyectil_base.h"
#include "../objetos_juego/particula_base.h"
#include "../objetos_juego/trazador_humo.h"

namespace App_Juego_Contenedores
{

struct Contenedor_volatiles
{
	//TODO: Todo esto podrían ser unique_pointers...
	typedef std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base> sptr_Proyectil_base;
	typedef std::shared_ptr<App_Juego_ObjetoJuego::Particula_base> sptr_Particula_base;
	typedef std::shared_ptr<App_Juego_ObjetoJuego::Trazador_humo> sptr_Trazador_humo;

	typedef std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base> > Vsptr_Proyectil_base;
	typedef std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Particula_base> > Vsptr_Particula_base;
	typedef std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Trazador_humo> > Vsptr_Trazador_humo;

	void						vaciar();
	void						fusionar_con(Contenedor_volatiles&);
	size_t						limpiar_para_borrar();
	size_t						size() const;

	Vsptr_Proyectil_base		 		proyectiles_jugador;
	Vsptr_Proyectil_base		 		proyectiles_enemigos;
	Vsptr_Particula_base				particulas;
	Vsptr_Trazador_humo				trazadores;
};
}

#endif
