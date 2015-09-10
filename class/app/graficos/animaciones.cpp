#include "animaciones.h"

using namespace App_Graficos;

const HerramientasProyecto::Tabla_animaciones& Animaciones::obtener(size_t v) const
{
	return animaciones.at(v);
}

/**
* @throw std::runtime error por animaciones y frames si algo va mal...
*/

void Animaciones::cargar()
{	
	//Cargar las tablas de sprites...
	auto f=[this](const std::string& ruta_frames, const std::string& ruta_animaciones, size_t indice)
	{
		HerramientasProyecto::Tabla_sprites ts(ruta_frames);
		animaciones.insert(std::make_pair(indice, HerramientasProyecto::Tabla_animaciones(ts, ruta_animaciones)));
	};

	using namespace App_Definiciones;

	f("data/hojas/sprites_hoja.dat", "data/hojas/sprites_anim.dat", sprites);
	f("data/hojas/particulas_hoja.dat", "data/hojas/particulas_anim.dat", particulas);
}
