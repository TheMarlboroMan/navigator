#include "particula_explosion.h"

using namespace App_Juego_ObjetoJuego;

HerramientasProyecto::Tabla_sprites Particula_explosion::tabla_sprites("data/recursos/particulas.dat");

Particula_explosion::Particula_explosion(float x, float y, float tv, const DLibH::Vector_2d& v):
	App_Interfaces::Objeto_juego_I(),
	Particula_base(tv),
	App_Juego::Actor_movil(x, y, 1.0, 1.0),
	frame_actual(App_Definiciones::Sprites_particulas::explosion_01)
{
	establecer_vector(v);
}

unsigned short int Particula_explosion::obtener_profundidad_ordenacion()const
{
	return 30;
}

void Particula_explosion::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::TR_BITMAP);
	b.establecer_alpha(192);
	b.establecer_recurso(App::Recursos_graficos::rt_particulas);

	const auto& f=tabla_sprites.obtener(frame_actual);
	b.establecer_recorte(f.x, f.y, f.w, f.h);

	//TODO: Esto está mal seguro: el frame va cambiando de tamaño y hay que centrarlo en la posición
	//de turno.
	float pos_x=acc_espaciable_x();
	float pos_y=acc_espaciable_y();

	b.establecer_posicion(pos_x, pos_y, f.w, f.w);

	//TODO: Ya hablaremos de cómo hacer el humo...
}

void Particula_explosion::turno(float delta)
{
	restar_tiempo_vida(delta);
	//TODO: Calcular el frame actual en base a Particula_base::calcular_parcial_tiempo_vida();
}

float Particula_explosion::obtener_peso() const
{
	return 0.0;
}
float Particula_explosion::obtener_max_velocidad_caida() const
{
	return 0.0;
}

void Particula_explosion::callback_ajuste(float pos, posiciones_ajuste tipo)
{
	//Nada de nada...
}
