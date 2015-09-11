#include "particula_chatarra.h"

using namespace App_Juego_ObjetoJuego;

Particula_chatarra::Particula_chatarra(float x, float y, float tv, const DLibH::Vector_2d& v):
	Particula_movil_base(x, y, tv, v),
	frame(0)
{
	//Escoger frame.
	using def=App_Definiciones::definiciones_particulas;
	auto g=HerramientasProyecto::Generador_int(def::min_chatarra, def::max_chatarra);
	frame=g();
}

unsigned short int Particula_chatarra::obtener_profundidad_ordenacion()const
{
	return 30;
}

void Particula_chatarra::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(255);
	b.establecer_recurso(App::Recursos_graficos::rt_particulas);

//TODO TODO TODO
//	const auto& f=acc_tabla_sprites().obtener(frame);
//	b.establecer_recorte(f.x, f.y, W, H);
	b.establecer_posicion(acc_espaciable_x(), acc_espaciable_y(), W, H);
}
