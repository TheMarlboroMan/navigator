#include "particula_fantasma_bonus_tiempo.h"

using namespace App_Juego_ObjetoJuego;

Particula_fantasma_bonus_tiempo::Particula_fantasma_bonus_tiempo(float x, float y, float tv, float ve)
	:Particula_fantasma(x, y, tv, ve)
{

}

unsigned short int Particula_fantasma_bonus_tiempo::obtener_profundidad_ordenacion()const
{
	return 25;
}

unsigned int Particula_fantasma_bonus_tiempo::obtener_ciclos_representable()const
{
	return 1;
}

void Particula_fantasma_bonus_tiempo::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	using namespace App_Definiciones;
	const auto& f=b.obtener_frame(animaciones::sprites, animaciones_sprites::bonus_tiempo, 0);

	float alpha=calcular_parcial_tiempo_vida(192);
	if(alpha < 0.0f) alpha=0.0f;

	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(alpha);
	b.establecer_recurso(App::Recursos_graficos::rt_juego);
	b.establecer_recorte(f.x, f.y, f.w, f.h);
	b.establecer_posicion(x, y, f.w+extra_w, f.h+extra_h);
}
