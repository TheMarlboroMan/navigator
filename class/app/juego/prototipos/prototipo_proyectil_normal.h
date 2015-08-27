#ifndef PROTOTIPO_PROYECTIL_NORMAL_I
#define PROTOTIPO_PROYECTIL_NORMAL_I

#include <herramientas/vector_2d/vector_2d.h>
#include "alpha_prototipo.h"
#include "../objetos_juego/proyectil_normal.h"

namespace App_Juego_Prototipos
{

class Prototipo_proyectil_normal:
	public Alpha_prototipo
{
	//////////////////////
	//Interface pública...
	public:

				Prototipo_proyectil_normal(float x, float y, int w, int h, const DLibH::Vector_2d& v, float potencia, App_Juego_ObjetoJuego::Proyectil_normal::colores color);
	virtual void		crear_objeto_juego(App_Interfaces::Factoria_objetos_juego_I&);

	//////////////////////
	//Internas...
	private:

	float							x, y;
	int							w, h;
	DLibH::Vector_2d					v;
	float							potencia;
	App_Juego_ObjetoJuego::Proyectil_normal::colores	color;
};

}

#endif
