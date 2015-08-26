#include "particula_explosion.h"

using namespace App_Juego_ObjetoJuego;

Particula_explosion::Particula_explosion(float x, float y, float tv, const DLibH::Vector_2d& v):
	Particula_movil_base(x, y, tv, v),
	frame_actual(App_Definiciones::Sprites_particulas::explosion_01),
	w(0.0f), h(0.0f)
{
	mut_fuerza_frenado(25.0f);
}

unsigned short int Particula_explosion::obtener_profundidad_ordenacion()const
{
	return 30;
}

void Particula_explosion::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::TR_BITMAP);
	
	float alpha=calcular_parcial_tiempo_vida(255);
	if(alpha < 0.0f) alpha=0.0f;

	b.establecer_alpha(alpha);
	b.establecer_recurso(App::Recursos_graficos::rt_particulas);

	const auto& f=acc_tabla_sprites().obtener(frame_actual);
	b.establecer_recorte(f.x, f.y, f.w, f.h);

	//Centramos la posición según el ancho del frame anterior.
	float pos_x=acc_espaciable_x()-(w / 2);
	float pos_y=acc_espaciable_y()-(h / 2);

	w=f.w;
	h=f.h;

	b.establecer_posicion(pos_x, pos_y, w, h);

	//TODO: Ya hablaremos de cómo hacer el humo...
}

void Particula_explosion::turno(float delta)
{
	Particula_movil_base::turno(delta);

	//La selección del frame.
	int lon=App_Definiciones::Sprites_particulas::lon_explosion;
	frame_actual=App_Definiciones::Sprites_particulas::explosion_01+(lon - calcular_parcial_tiempo_vida(lon));
}
