#include "prototipo_proyectil_normal.h"

using namespace App_Juego_Prototipos;

Prototipo_proyectil_normal::Prototipo_proyectil_normal(float x, float y, int w, int h, const DLibH::Vector_2d& v, float potencia, App_Juego_ObjetoJuego::Proyectil_normal::colores color)
	:x(x), y(y), w(w), h(h), v(v), potencia(potencia), color(color)
{
	
}

void Prototipo_proyectil_normal::crear_objeto_juego(App_Interfaces::Factoria_objetos_juego_I& f)
{
//TODO TODO
//	using namespace App_Juego_ObjetoJuego;
//	auto ptr=std::shared_ptr<Proyectil_normal>(new Proyectil_normal(x, y, w, h, v, potencia, color));
//	f.insertar(ptr);
}
