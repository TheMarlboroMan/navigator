#include "obstaculo_generico.h"

using namespace App_Juego_ObjetoJuego;

Obstaculo_generico::Obstaculo_generico(float x, float y, int tipo)
	//TODO... Escoger W y H de alguna parte...
	:Actor(x, y, 15, 22),
	Objeto_juego_I(),
	tipo(tipo)
{
	//TODO: En función del tipo extraer sus propiedades. Posiblemente
	//sea un objeto estático que se inicialice, lea un fichero y contenga
	//las informaciones de tamaño.
	
	//TODO: Odiamos las cosas estáticas... Mejor que se inicialice en un 
	//punto conocido...
}


unsigned short int Obstaculo_generico::obtener_profundidad_ordenacion()const
{
	//TODO: Quizás pueda ser parte de la definición del propio objeto?.
	return 10;
}

void Obstaculo_generico::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	using namespace App_Definiciones;
	const auto& f=b.obtener_frame(animaciones::sprites, animaciones_sprites::obstaculo_generico, 0);

	b.establecer_tipo(App_Graficos::Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(255);
	b.establecer_recurso(App::Recursos_graficos::rt_juego);
	b.establecer_recorte(f.x, f.y, f.w, f.h);
	b.establecer_posicion(acc_espaciable_x()+f.desp_x, acc_espaciable_y()+f.desp_y, 15, 22); //w, h);

}
