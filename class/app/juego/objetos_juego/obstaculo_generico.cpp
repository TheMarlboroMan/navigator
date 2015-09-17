#include "obstaculo_generico.h"

using namespace App_Juego_ObjetoJuego;

Obstaculo_generico::Obstaculo_generico(float x, float y, int tipo, const App_Lectores::Info_obstaculos_genericos& iog)
	:Actor(x, y, 0, 0),
	Objeto_juego_I(),
	tipo(tipo), indice_animacion(0)
{
	try
	{
		const auto& info=iog.obtener(tipo);
		mut_w_caja(info.w);
		mut_h_caja(info.h);
		indice_animacion=info.indice_animacion;
	}
	catch(std::out_of_range& e)
	{
		LOG<<"ERROR: Obstáculo genérico fuera de rango al intentar cargar tipo "<<tipo<<std::endl;
		throw;
	}
}


unsigned short int Obstaculo_generico::obtener_profundidad_ordenacion()const
{
	//TODO: Quizás pueda ser parte de la definición del propio objeto?.
	return 10;
}

unsigned int Obstaculo_generico::obtener_ciclos_representable()const
{
	return 1;
}

void Obstaculo_generico::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	using namespace App_Definiciones;
	const auto& f=b.obtener_frame(animaciones::sprites, indice_animacion, 0);

	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(255);
	b.establecer_recurso(App::Recursos_graficos::rt_juego);
	b.establecer_recorte(f.x, f.y, f.w, f.h);
	b.establecer_posicion(acc_espaciable_x()+f.desp_x, acc_espaciable_y()+f.desp_y, 15, 22); //w, h);

}
