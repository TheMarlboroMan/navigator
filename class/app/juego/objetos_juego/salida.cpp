#include "salida.h"

using namespace App_Juego_ObjetoJuego;

Salida::Salida(App_Definiciones::t_dim px, App_Definiciones::t_dim py)
	:Objeto_juego_I(),
	x(px), y(py)
{

}

App_Interfaces::Espaciable::t_caja Salida::copia_caja() const
{
	using namespace App_Definiciones;
	return Espaciable::t_caja(x, y, definiciones::dim_celda, definiciones::dim_celda);
}

unsigned short int Salida::obtener_profundidad_ordenacion()const
{
	return 10;
}

void Salida::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	using namespace App_Graficos;

	b.establecer_tipo(Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(255);
	b.establecer_recurso(App::Recursos_graficos::rt_defecto);
	b.establecer_recorte(32, 32, W, H);
	b.establecer_posicion(acc_espaciable_x(), acc_espaciable_y(), W, H);
}

void Salida::efecto_colision(App_Interfaces::Efecto_colision_recogedor_I& ec)
{
	if(ec.es_jugador_aterrizado())
	{
		ec.marcar_como_salida_nivel();
	}
}
