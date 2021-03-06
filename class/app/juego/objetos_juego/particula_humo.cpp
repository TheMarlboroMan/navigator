#include "particula_humo.h"

using namespace App_Juego_ObjetoJuego;

Particula_humo::Particula_humo(float x, float y, float tv):
	Particula_base(tv),
	x(x), y(y),
	w(0.0f), h(0.0f)
{

}

unsigned short int Particula_humo::obtener_profundidad_ordenacion()const
{
	return 30;
}

unsigned int Particula_humo::obtener_ciclos_representable()const
{
	return 1;
}

void Particula_humo::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	using namespace App_Definiciones;
	//Pasamos el tiempo de vida para hacer efecto "reverse".
	const auto& f=b.obtener_animacion(animaciones::particulas, animaciones_particulas::humo).obtener_para_tiempo_animacion(acc_tiempo_vida(), acc_tiempo_vida_inicial()).frame;

	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(127);
	b.establecer_recurso(App::Recursos_graficos::rt_particulas);
	b.establecer_recorte(f.x, f.y, f.w, f.h);

	//Centramos la posición según el ancho del frame anterior.
	float pos_x=x-(w / 2);
	float pos_y=y-(h / 2);

	w=f.w;
	h=f.h;

	b.establecer_posicion(pos_x, pos_y, w, h);
}

void Particula_humo::turno(App_Interfaces::Contexto_turno_I& ct)
{
	restar_tiempo_vida(ct.acc_delta());
}
