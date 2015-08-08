#include "bonus_tiempo.h"
#include "../../recursos.h"

using namespace App_Juego_ObjetoJuego;
using namespace App_Graficos;
using namespace App;

const float Bonus_tiempo::CANTIDAD_TIEMPO_DEFECTO=10.0f;

Bonus_tiempo::Bonus_tiempo(float x, float y, float t):
	Actor(x, y, W, H),
	Objeto_juego_I(),
	tiempo(t)
{
	//TODO: Fuck repeticiones.
	App_Interfaces::Facetador& f=como_facetador();
	f.mut_objeto_juego(this).
		mut_bonus(this).
		mut_representable(this).
		mut_espaciable(this);
}

unsigned short int Bonus_tiempo::obtener_profundidad_ordenacion()const
{
	//TODO.
	return 10;
}

void Bonus_tiempo::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	//TODO...
	//Se asume que todos los frames van mirando a la derecha.
	b.establecer_tipo(Bloque_transformacion_representable::tipos::TR_BITMAP);
	b.establecer_alpha(255);
	b.establecer_recurso(Recursos_graficos::RT_DEFECTO);
	b.establecer_recorte(0, 32, W, H);
	b.establecer_posicion(acc_espaciable_x(), acc_espaciable_y(), W, H);
}
