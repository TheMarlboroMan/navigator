#ifndef REPRESENTADOR_H
#define REPRESENTADOR_H

#include "bloque_transformacion_representable.h"
#include "../definiciones/definiciones.h"
#include "../interfaces/representable_i.h"


/*El representador funciona de la siguiente forma: desde el controlador 
generamos un array de punteros a "Representables". Se le pasa el array al 
representador que primero lo ordena por profundidad y luego genera un bloque de
transformación que pasa y procesa para cada uno de ellos.

El representador, por supuesto, sólo funciona con aquellas entidades que sean
"Representable", esto es, para todo aquello que forme parte del mundo. HUDS,
mensajes y otras cosas irían representadas de otro modo.
*/

namespace App_Graficos
{

class Representador
{
	/////////////////////////
	// Interface pública

	public:

	unsigned int 				generar_vista(DLibV::Pantalla&, DLibV::Camara&, const std::vector<const App_Interfaces::Representable_I *>&);
	unsigned int 				generar_vista(DLibV::Pantalla&, const std::vector<const App_Interfaces::Representable_I *>&);
	void 					generar_hud(DLibV::Pantalla& pantalla, int salud, int energia, int escudo, std::string tiempo);
	void 					dibujar_marco_automapa(DLibV::Pantalla&);
	void 					dibujar_pieza_automapa(DLibV::Pantalla&, int x, int y, App_Definiciones::direcciones t, bool es_actual);

	private:

	/////////////////////////
	// Definiciones

	static const int 			W_FONDO_HUD=640;
	static const int 			H_FONDO_HUD=80;
	static const int 			X_FONDO_HUD=0;
	static const int 			Y_FONDO_HUD=480;

	static const int 			X_AUTOMAPA=400;
	static const int 			Y_AUTOMAPA=412;
	static const int 			DIM_AUTOMAPA=7;

	/////////////////////////
	// Propiedades
	
	private:

	Bloque_transformacion_representable 	bloque_transformacion;
};
}
#endif
