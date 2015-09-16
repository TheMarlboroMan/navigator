#include "enemigo_tanque.h"

using namespace App_Juego_ObjetoJuego;

const float Enemigo_tanque::SALUD_DEFECTO=30.0f;
const float Enemigo_tanque::TIEMPO_PROXIMO_DISPARO_DEFECTO=3.0f;

Enemigo_tanque::Enemigo_tanque(float px, float py, float s)
	:
	Objeto_juego_I(),
	Actor(px, py, W, H),
	salud(s),
	tiempo_proximo_disparo(TIEMPO_PROXIMO_DISPARO_DEFECTO),
	angulo(0.0)
{

}

unsigned short int Enemigo_tanque::obtener_profundidad_ordenacion()const
{
	return 10;
}


void Enemigo_tanque::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
{
	using namespace App_Graficos;
	using namespace App_Definiciones;
	using BMP=DLibV::Representacion_bitmap_dinamica;

	const auto& f1=b.obtener_frame(animaciones::sprites, animaciones_sprites::enemigo_tanque, 0);
	const auto& f2=b.obtener_frame(animaciones::sprites, animaciones_sprites::enemigo_tanque_canon, 0);

	//Se asume que todos los frames van mirando a la derecha.
	b.establecer_tipo(Bloque_transformacion_representable::tipos::tr_grupo_dinamico);

	BMP * cuerpo=new BMP();
	cuerpo->establecer_textura(DLibV::Gestor_texturas::obtener(App::Recursos_graficos::rt_juego));
	cuerpo->establecer_recorte(f1.x+f1.desp_x, f1.y+f1.desp_y, f1.w, f1.h);
	cuerpo->establecer_posicion(0, 0, f1.w, f1.h);

	BMP * canon=new BMP();
	canon->establecer_textura(DLibV::Gestor_texturas::obtener(App::Recursos_graficos::rt_juego));
	canon->establecer_recorte(f2.x+f2.desp_x, f2.y+f2.desp_y, f2.w, f2.h);
	canon->establecer_posicion(10, -5, f2.w, f2.h);
	canon->transformar_centro_rotacion(2, 9);
	canon->transformar_rotar(angulo);

	b.insertar_en_grupo(cuerpo);
	b.insertar_en_grupo(canon);
	b.establecer_posicion(acc_espaciable_x(), acc_espaciable_y(), W, H);
}

void Enemigo_tanque::turno(App_Interfaces::Contexto_turno_I& ct)
{
	float delta=ct.acc_delta();
	tiempo_proximo_disparo-=delta;

	angulo=obtener_vector_para(ct.acc_blanco()).angulo_grados() + 90.0f;
}

void Enemigo_tanque::recibir_disparo(float potencia)
{
	int id_sonido=App::Recursos_audio::rs_explosion;

	salud-=potencia;
	if(salud <= 0.0) 
	{
		mut_borrar(true);
	}
	else
	{
		id_sonido=App::Recursos_audio::rs_golpe;
	}

	insertar_reproducir(App_Audio::Info_audio_reproducir(
		App_Audio::Info_audio_reproducir::t_reproduccion::simple,
		App_Audio::Info_audio_reproducir::t_sonido::repetible,  
		id_sonido, 127, 127));
}

void Enemigo_tanque::generar_objetos(App_Interfaces::Factoria_objetos_juego_I& f)
{
	//TODO: Esto se repite a saco...
	if(es_borrar())
	{
		const auto& v=DLibH::Vector_2d(0.f, 0.f);

		float x=acc_espaciable_x()+(acc_espaciable_w()/2);
		float y=acc_espaciable_y()+(acc_espaciable_w()/2);
		auto g=HerramientasProyecto::Generador_int(10, 30);
		auto gvel=HerramientasProyecto::Generador_int(150, 300);
		int i=0, mp=g();
		while(i < mp)
		{
			auto g=HerramientasProyecto::Generador_int(0, 359);
			auto v=Vector_2d::vector_unidad_para_angulo(g())*gvel();
			f.fabricar_chatarra(x, y, 3.0f, v);
			++i;
		}

		auto gtraza=HerramientasProyecto::Generador_int(3, 5);
		auto gveltraza=HerramientasProyecto::Generador_int(160, 200);
		auto gduracion=HerramientasProyecto::Generador_int(40, 100);
		i=0;
		while(i < gtraza())
		{
			auto g=HerramientasProyecto::Generador_int(0, 359);
			auto v=Vector_2d::vector_unidad_para_angulo(g())*gveltraza();
			float dur=(float)gduracion() / 100.0;
			f.fabricar_trazador_humo(x, y, dur, v);
			++i;
		}

		f.fabricar_bonus_tiempo(acc_espaciable_x(), acc_espaciable_y(), 5.0f);
		f.fabricar_explosion(x, y, 1.0f, v);
	}
	else
	{
		if(tiempo_proximo_disparo < 0.0f) 
		{
			tiempo_proximo_disparo=TIEMPO_PROXIMO_DISPARO_DEFECTO;

			const auto v=obtener_vector_para(f.acc_blanco_disparo()) * 200.0f;

			//TODO: X e Y deben estar un movidos fuera del tanque o algo así, porque
			//el proyectil choca con el propio tanque si lo hacemos sólido :S.

			f.fabricar_proyectil_normal_enemigo(acc_espaciable_x()+ (acc_espaciable_w() / 2), acc_espaciable_y(), 8, 8, v, 25.0);

			//TODO: Los concerns de audio están mezlados con el resto :(.
			insertar_reproducir(App_Audio::Info_audio_reproducir(
				App_Audio::Info_audio_reproducir::t_reproduccion::simple,
				App_Audio::Info_audio_reproducir::t_sonido::repetible,  
				App::Recursos_audio::rs_disparo, 127, 127));
		}
	}
}

void Enemigo_tanque::efecto_colision(App_Interfaces::Efecto_colision_recogedor_I& er)
{
	er.recibir_impacto(2.5f);
}
