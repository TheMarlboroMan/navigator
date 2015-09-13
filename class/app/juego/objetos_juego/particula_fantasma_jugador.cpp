#include "particula_fantasma_jugador.h"

using namespace App_Juego_ObjetoJuego;

Particula_fantasma_jugador::Particula_fantasma_jugador(float x, float y, float tv, float ve, App_Definiciones::direcciones direccion)
	:Particula_fantasma(x, y, tv, ve), direccion(direccion)
{

}

void Particula_fantasma_jugador::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	using namespace App_Definiciones;
	const auto& f=b.obtener_frame(animaciones::sprites, animaciones_sprites::jugador, 0);

	float alpha=calcular_parcial_tiempo_vida(192);
	if(alpha < 0.0f) alpha=0.0f;

	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(alpha);
	b.establecer_recurso(App::Recursos_graficos::rt_juego);
	b.establecer_recorte(f.x, f.y, f.w, f.h);
	b.establecer_posicion(x, y, f.w+extra_w, f.h+extra_h);
	b.invertir_horizontal(direccion==App_Definiciones::direcciones::izquierda);
}
