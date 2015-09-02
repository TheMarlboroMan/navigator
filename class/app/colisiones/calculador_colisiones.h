#ifndef CALCULADOR_COLISIONES_H
#define CALCULADOR_COLISIONES_H

#include "../niveles/sala.h"
#include "../juego/actor_movil.h"
#include "../definiciones/definiciones.h"
#include <algorithm>

namespace App_Colisiones
{

class Calculador_colisiones
{
	public:

	std::vector<const App_Niveles::Celda *> 	celdas_en_caja(const App_Interfaces::Espaciable::t_caja& caja, const App_Niveles::Sala& sala) const;
	std::vector<const App_Interfaces::Espaciable *> solidos_en_caja_sala(const App_Interfaces::Espaciable::t_caja& caja, const App_Niveles::Sala& sala) const;

	void 						ajustar_colisiones_eje_y_actor_movil_con_espaciables(App_Juego::Actor_movil& actor, const std::vector<const App_Interfaces::Espaciable * >& espaciables) const;
	void 						ajustar_colisiones_eje_x_actor_movil_con_espaciables(App_Juego::Actor_movil& actor, const std::vector<const App_Interfaces::Espaciable * >& espaciables) const;

	bool 						es_fuera_de_sala(const App_Interfaces::Espaciable::t_caja& caja, const App_Niveles::Sala& sala) const;
};

}

#endif
