#include "particula_chatarra.h"

using namespace App_Juego_ObjetoJuego;

Particula_chatarra::Particula_chatarra(float x, float y, float tv, const DLibH::Vector_2d& v):
	App_Interfaces::Objeto_juego_I(),
	Particula_base(tv),
	App_Juego::Actor_movil(x, y, 1.0, 1.0),
	frame(0)
{
	using def=App_Definiciones::Sprites_particulas;
	auto g=HerramientasProyecto::Generador_int(def::chatarra_01_01, def::chatarra_08_04);
	frame=g();
	establecer_vector(v);
}

unsigned short int Particula_chatarra::obtener_profundidad_ordenacion()const
{
	return 30;
}

void Particula_chatarra::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::TR_BITMAP);
	b.establecer_alpha(255);
	b.establecer_recurso(App::Recursos_graficos::rt_particulas);

	const auto& f=acc_tabla_sprites().obtener(frame);
	b.establecer_recorte(f.x, f.y, W, H);
	b.establecer_posicion(acc_espaciable_x(), acc_espaciable_y(), W, H);
}

void Particula_chatarra::turno(float delta)
{
	restar_tiempo_vida(delta);

	//El movimiento...
	desplazar(delta);
	frenar(delta, 15.0f);
}

float Particula_chatarra::obtener_peso() const
{
	return 0.0f;
}
float Particula_chatarra::obtener_max_velocidad_caida() const
{
	return 0.0f;
}

void Particula_chatarra::callback_ajuste(float pos, posiciones_ajuste tipo)
{
	//Nada de nada...
}
