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
	LOG<<"Iniciando registro de animaciones..."<<std::endl;

	//Cargar las tablas de sprites...
	auto f=[this](const std::string& ruta_frames, const std::string& ruta_animaciones, size_t indice)
	{
		LOG<<"Registrando animaciones "<<indice<<" -> "<<ruta_frames<<" -> "<<ruta_animaciones<<std::endl;
		HerramientasProyecto::Tabla_sprites ts(ruta_frames);
		if(animaciones.count(indice)) throw std::runtime_error("Ya existe tabla de animaciones al cargar tablas!!");
		else animaciones.insert(std::make_pair(indice, HerramientasProyecto::Tabla_animaciones(ts, ruta_animaciones)));
	};

	using namespace App_Definiciones;

	f("data/hojas/juego_hoja.dat", "data/hojas/juego_anim.dat", sprites);
	f("data/hojas/particulas_hoja.dat", "data/hojas/particulas_anim.dat", particulas);
	f("data/hojas/celdas_hoja.dat", "data/hojas/celdas_anim.dat", celdas_template);
}
