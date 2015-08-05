#include "bonus_salud.h"
#include "../../recursos.h"

using namespace App_Juego_ObjetoJuego;
using namespace App_Graficos;
using namespace App;

const float Bonus_salud::CANTIDAD_SALUD_DEFECTO=15.0f;

Bonus_salud::Bonus_salud():
	Actor(),
	Borrable_I(),
	salud(CANTIDAD_SALUD_DEFECTO)
{

}

Bonus_salud::Bonus_salud(float x, float y, float s):
	Actor(x, y, W, H),
	salud(s)
{

}

unsigned short int Bonus_salud::obtener_profundidad_ordenacion()const
{
	//TODO.
	return 10;
}

void Bonus_salud::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	//TODO...
	//Se asume que todos los frames van mirando a la derecha.
	b.establecer_tipo(Bloque_transformacion_representable::tipos::TR_BITMAP);
	b.establecer_alpha(255);
	b.establecer_recurso(Recursos_graficos::RT_DEFECTO);
	b.establecer_recorte(16, 32, W, H);
	b.establecer_posicion(acc_espaciable_x(), acc_espaciable_y(), W, H);
}
