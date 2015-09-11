#ifndef ANIMACIONES_H
#define ANIMACIONES_H

#include <map>

#include <herramientas/log_base/log_base.h>

#include "../../herramientas_proyecto/tabla_animaciones.h"
#include "../definiciones/animaciones.h"

extern DLibH::Log_base LOG;

namespace App_Graficos
{

class Animaciones
{
	public:

	const HerramientasProyecto::Tabla_animaciones&			obtener(size_t) const;
	void								cargar();

	private:

	std::map<size_t, HerramientasProyecto::Tabla_animaciones>	animaciones;
};

}

#endif
