#include "bonus_tiempo.h"
#include "../../recursos.h"

using namespace App_Juego_ObjetoJuego;
using namespace App_Graficos;
using namespace App;

const float Bonus_tiempo::CANTIDAD_TIEMPO_DEFECTO=10.0f;

Bonus_tiempo::Bonus_tiempo(float x, float y, float t):
	Objeto_juego_I(),
	Actor(x, y, W, H),
	tiempo(t)
{

}

unsigned short int Bonus_tiempo::obtener_profundidad_ordenacion()const
{
	return 10;
}

void Bonus_tiempo::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	//TODO: Reemplazar por hojas de sprites.
	b.establecer_tipo(Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(255);
	b.establecer_recurso(Recursos_graficos::rt_defecto);
	b.establecer_recorte(0, 32, W, H);
	b.establecer_posicion(acc_espaciable_x(), acc_espaciable_y(), W, H);
}

void Bonus_tiempo::efecto_colision(App_Interfaces::Efecto_colision_recogedor_I& ec)
{
	ec.sumar_tiempo(tiempo);
	mut_borrar(true);
	
	using namespace App_Audio;
	insertar_reproducir(Info_audio_reproducir(
		Info_audio_reproducir::t_reproduccion::simple, 
		Info_audio_reproducir::t_sonido::repetible, 
		App::Recursos_audio::rs_recoger_bonus, 127, 127));
}

void Bonus_tiempo::generar_objetos(App_Interfaces::Factoria_objetos_juego_I& f)
{
	if(es_borrar())
	{
		f.fabricar_fantasma(
		acc_espaciable_x(), acc_espaciable_y(), 0.8f, 10.0f, App_Definiciones::direcciones::derecha,
		App::Recursos_graficos::rt_defecto, 
		DLibH::Caja<int, int>(16, 32, W, H));
	}
}
