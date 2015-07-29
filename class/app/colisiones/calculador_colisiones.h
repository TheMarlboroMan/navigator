#ifndef CALCULADOR_COLISIONES_H
#define CALCULADOR_COLISIONES_H

#include "../niveles/sala.h"
#include "../juego/actor_movil.h"

namespace App_Colisiones
{

class Calculador_colisiones
{
	public:

	std::vector<const App_Niveles::Celda *> celdas_en_caja(const App_Interfaces::Espaciable::t_caja& caja, const App_Niveles::Sala& sala) const;	
	void ajustar_colisiones_actor_movil_y_con_celdas(App_Juego::Actor_movil& actor, const std::vector<const App_Niveles::Celda * >& celdas) const;
	void ajustar_colisiones_actor_movil_x_con_celdas(App_Juego::Actor_movil& actor, const std::vector<const App_Niveles::Celda * >& celdas) const;
};

}

#endif
