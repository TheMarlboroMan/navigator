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
	//TODO: Reemplazar por hojas de sprites.
	b.establecer_tipo(Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(255);
	b.establecer_recurso(Recursos_graficos::rt_defecto);
	b.establecer_recorte(16, 32, W, H);
	b.establecer_posicion(acc_espaciable_x(), acc_espaciable_y(), W, H);
}

void Bonus_salud::recoger(App_Interfaces::Recoge_bonus_I& rb)
{
	if(rb.puede_recoger_salud())
	{
		rb.sumar_salud(salud);
		Bonus_I::recoger(rb);

		auto ptr=std::shared_ptr<App_Juego_Particulas::Definicion_particula>(new App_Juego_Particulas::Definicion_particula_fantasma(
			acc_espaciable_x(), acc_espaciable_y(), 0.8f, 10.0f, App_Definiciones::direcciones::derecha,
			App::Recursos_graficos::rt_defecto, 
			DLibH::Caja<int, int>(16, 32, W, H)));
		insertar_prototipo(ptr);

		using namespace App_Audio;
		insertar_reproducir(Info_audio_reproducir(
			Info_audio_reproducir::t_reproduccion::simple, 
			Info_audio_reproducir::t_sonido::repetible, 
			App::Recursos_audio::rs_recoger_bonus, 127, 127));
	}
}
