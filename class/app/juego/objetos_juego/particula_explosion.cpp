#include "particula_explosion.h"

using namespace App_Juego_ObjetoJuego;

Particula_explosion::Particula_explosion(float x, float y, float tv, const DLibH::Vector_2d& v):
	Particula_movil_base(x, y, tv, v),
	w(0.0f), h(0.0f)
{
	mut_fuerza_frenado(25.0f);
}

unsigned short int Particula_explosion::obtener_profundidad_ordenacion()const
{
	return 30;
}

unsigned int Particula_explosion::obtener_ciclos_representable()const
{
	return 1;
}

void Particula_explosion::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	using namespace App_Definiciones;
	const auto& f=b.obtener_animacion(animaciones::particulas, animaciones_particulas::explosion).obtener_para_tiempo_animacion(acc_tiempo_activa(), acc_tiempo_vida_inicial()).frame;
	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_bitmap);

	float alpha=calcular_parcial_tiempo_vida(255);
	if(alpha < 0.0f) alpha=0.0f;

	b.establecer_alpha(alpha);
	b.establecer_recurso(App::Recursos_graficos::rt_particulas);
	b.establecer_recorte(f.x, f.y, f.w, f.h);

	//Centramos la posición según el ancho del frame anterior.
	float pos_x=acc_espaciable_x()-(w / 2);
	float pos_y=acc_espaciable_y()-(h / 2);

	w=f.w;
	h=f.h;

	b.establecer_posicion(pos_x, pos_y, w, h);
}

void Particula_explosion::turno(App_Interfaces::Contexto_turno_I& ct)
{
	Particula_movil_base::turno(ct);
}
