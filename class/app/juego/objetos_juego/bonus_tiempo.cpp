#include "bonus_tiempo.h"
#include "../../recursos.h"

using namespace App_Juego_ObjetoJuego;
using namespace App_Graficos;
using namespace App;

const float Bonus_tiempo::CANTIDAD_TIEMPO_DEFECTO=10.0f;

Bonus_tiempo::Bonus_tiempo(float x, float y, float t):
	Objeto_juego_I(),
	Actor(x, y, W, H),
	tiempo(t)
{

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
	b.establecer_recurso(Recursos_graficos::rt_defecto);
	b.establecer_recorte(0, 32, W, H);
	b.establecer_posicion(acc_espaciable_x(), acc_espaciable_y(), W, H);
}
