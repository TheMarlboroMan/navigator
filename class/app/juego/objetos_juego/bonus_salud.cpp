#include "bonus_salud.h"
#include "../../recursos.h"

using namespace App_Juego_ObjetoJuego;
using namespace App_Graficos;
using namespace App;

const float Bonus_salud::CANTIDAD_SALUD_DEFECTO=15.0f;

Bonus_salud::Bonus_salud(float x, float y, float s):
	Objeto_juego_I(),
	Actor(x, y, W, H),
	salud(s)
{

}

unsigned short int Bonus_salud::obtener_profundidad_ordenacion()const
{
	return 10;
}

void Bonus_salud::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	using namespace App_Definiciones;
	const auto& f=b.obtener_frame(animaciones::sprites, animaciones_sprites::bonus_salud, 0);

	b.establecer_tipo(Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(255);
	b.establecer_recurso(Recursos_graficos::rt_juego);
	b.establecer_recorte(f.x, f.w, f.w, f.h);
	b.establecer_posicion(acc_espaciable_x()+f.desp_x, acc_espaciable_y()+f.desp_y, W, H);
}

void Bonus_salud::efecto_colision(App_Interfaces::Efecto_colision_recogedor_I& ec)
{
	if(ec.puede_recoger_salud())
	{
		ec.sumar_salud(salud);
		mut_borrar(true);

		using namespace App_Audio;
		insertar_reproducir(Info_audio_reproducir(
			Info_audio_reproducir::t_reproduccion::simple, 
			Info_audio_reproducir::t_sonido::repetible, 
			App::Recursos_audio::rs_recoger_bonus, 127, 127));
	}
}

void Bonus_salud::generar_objetos(App_Interfaces::Factoria_objetos_juego_I& f)
{
	if(es_borrar())
	{
//TODO: EEERRROR.... No tenemos acceso a los frames desde aquí!!!!!...
//		using namespace App_Definiciones;
//		const auto& frame=b.obtener_frame(animaciones::sprites, animaciones_sprites::bonus_salud, 0);

//		f.fabricar_fantasma(
//		acc_espaciable_x(), acc_espaciable_y(), 0.8f, 10.0f, App_Definiciones::direcciones::derecha,
//		App::Recursos_graficos::rt_juego, 
//		DLibH::Caja<int, int>(frame.x, frame.y, frame.w, frame.h));
	}
}
