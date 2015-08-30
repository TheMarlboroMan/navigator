#ifndef CONTEXTO_TURNO_JUEGO_H
#define CONTEXTO_TURNO_JUEGO_H

#include "../../interfaces/contexto_turno_i.h"
#include "../../niveles/sala.h"
#include "../jugador.h"
#include "../../colisiones/calculador_colisiones.h"

namespace App_Juego_Logica
{

class Contexto_turno_juego:
	public App_Interfaces::Contexto_turno_I
{
	public:
						Contexto_turno_juego(float, const App_Niveles::Sala& sala, App_Interfaces::Espaciable& jugador);

	virtual float				acc_delta() const {return delta;}
	virtual const App_Interfaces::Espaciable& acc_blanco() const {return jugador;}
	virtual bool				es_fuera_sala(const App_Interfaces::Espaciable::t_caja& e) const;
	virtual std::vector<const App_Interfaces::Espaciable *>	celdas_en_caja(const App_Interfaces::Espaciable::t_caja&e) const;

	private:

	float					delta;
	const App_Niveles::Sala&		sala;
	const App_Interfaces::Espaciable&	jugador;
};

}

#endif
