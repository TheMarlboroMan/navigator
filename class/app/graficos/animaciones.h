#ifndef ANIMACIONES_H
#define ANIMACIONES_H

#include <map>

#include <herramientas/log_base/log_base.h>

#include <tabla_animaciones.h>

#include "../definiciones/animaciones.h"

extern DLibH::Log_base LOG;

namespace App_Graficos
{

class Animaciones
{
	public:

	const Herramientas_proyecto::Tabla_animaciones&			obtener(size_t) const;
	void								cargar();

	private:

	std::map<size_t, Herramientas_proyecto::Tabla_animaciones>	animaciones;
};

}

#endif
