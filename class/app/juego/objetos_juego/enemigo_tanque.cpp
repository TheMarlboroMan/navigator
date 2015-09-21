#include "enemigo_tanque.h"

using namespace App_Juego_ObjetoJuego;

const float Enemigo_tanque::SALUD_DEFECTO=30.0f;
const float Enemigo_tanque::TIEMPO_PROXIMO_DISPARO_DEFECTO=3.0f;

Enemigo_tanque::Enemigo_tanque(float px, float py, int w, int h, float s)
	:
	Objeto_juego_I(),
	Actor(px, py, w, h),
	salud(s),
	tiempo_proximo_disparo(TIEMPO_PROXIMO_DISPARO_DEFECTO),
	angulo(0.0f)
{
}

Enemigo_tanque_abajo::Enemigo_tanque_abajo(float px, float py, float s)
	:Enemigo_tanque(px, py, W, H, s)
{

}

void Enemigo_tanque_abajo::transformar_cuerpo(App_Graficos::Bloque_transformacion_representable &b)const
{
	using namespace App_Definiciones;
	const auto f=b.obtener_frame(animaciones::sprites, animaciones_sprites::enemigo_tanque, 0);
	b.establecer_posicion(acc_espaciable_x(), acc_espaciable_y(), f.w, f.h);
	b.establecer_recorte(f.x, f.y, f.w, f.h);
}

float Enemigo_tanque_abajo::transformar_angulo_disparo(float a) const
{
	if(a > 180.0) a=180.0;
	else if(a < 0.f) a=0.f;
	return a;
}

bool Enemigo_tanque_abajo::validar_angulo_disparo(float a) const
{
	return a >= 0.f && a <= 180.0f;
}

Enemigo_tanque_arriba::Enemigo_tanque_arriba(float px, float py, float s)
	:Enemigo_tanque(px, py, W, H, s)
{
}

void Enemigo_tanque_arriba::transformar_cuerpo(App_Graficos::Bloque_transformacion_representable &b)const
{
	using namespace App_Definiciones;
	const auto f=b.obtener_frame(animaciones::sprites, animaciones_sprites::enemigo_tanque, 0);
	b.establecer_posicion(acc_espaciable_x(), acc_espaciable_y(), f.w, f.h);
	b.invertir_vertical(true);
	b.establecer_recorte(f.x, f.y, f.w, f.h);
}

float Enemigo_tanque_arriba::transformar_angulo_disparo(float a) const
{
	if(a > 360.0) a=360.0;
	else if(a < 180.f) a=180.f;
	return a;
}

bool Enemigo_tanque_arriba::validar_angulo_disparo(float a) const
{
	return a >= 180.f && a <= 360.0f;
}

Enemigo_tanque_derecha::Enemigo_tanque_derecha(float px, float py, float s)
	:Enemigo_tanque(px, py, W, H, s)
{
}

void Enemigo_tanque_derecha::transformar_cuerpo(App_Graficos::Bloque_transformacion_representable &b)const
{
	using namespace App_Definiciones;

	const auto f=b.obtener_frame(animaciones::sprites, animaciones_sprites::enemigo_tanque, 0);
	b.establecer_posicion(acc_espaciable_x(), acc_espaciable_y(), f.w, f.h);
	b.especificar_centro_rotacion(W / 2, W / 2);
	b.rotar(90);
	b.invertir_vertical(true); //En realidad estamos invirtiendo el vertical, y rotando.
	b.establecer_recorte(f.x, f.y, f.w, f.h);
}

float Enemigo_tanque_derecha::transformar_angulo_disparo(float a) const
{
	if(a > 270.0) a=270.0;
	else if(a < 90.f) a=90.f;
	return a;
}

bool Enemigo_tanque_derecha::validar_angulo_disparo(float a) const
{
	return a >= 90.f && a <= 270.0f;
}

Enemigo_tanque_izquierda::Enemigo_tanque_izquierda(float px, float py, float s)
	:Enemigo_tanque(px, py, W, H, s)
{
}

void Enemigo_tanque_izquierda::transformar_cuerpo(App_Graficos::Bloque_transformacion_representable &b)const
{
	using namespace App_Definiciones;

	const auto f=b.obtener_frame(animaciones::sprites, animaciones_sprites::enemigo_tanque, 0);
	b.establecer_posicion(acc_espaciable_x(), acc_espaciable_y(), f.w, f.h);
	b.especificar_centro_rotacion(W / 2, W / 2);
	b.rotar(90);
	b.establecer_recorte(f.x, f.y, f.w, f.h);
}

float Enemigo_tanque_izquierda::transformar_angulo_disparo(float a) const
{
	if(a > 90.f && a < 270.f) a=270.f;
	return a;
}

bool Enemigo_tanque_izquierda::validar_angulo_disparo(float a) const
{
	return (a >= 0.f && a <= 90.0f) || (a >= 270.f && a <=360.f);
}

/**************************************************/

unsigned short int Enemigo_tanque::obtener_profundidad_ordenacion()const
{
	return 10;
}

unsigned int Enemigo_tanque::obtener_ciclos_representable()const
{
	return 2;
}

void Enemigo_tanque::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
{
	using namespace App_Graficos;

	b.establecer_tipo(Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(255);
	b.establecer_recurso(App::Recursos_graficos::rt_juego);

	switch(b.acc_ciclo())
	{
		case 1: transformar_cuerpo(b); break;
		case 2: 
		{
			using namespace App_Definiciones;

			const auto f=b.obtener_frame(animaciones::sprites, animaciones_sprites::enemigo_tanque_canon, 0);
			b.especificar_centro_rotacion(2,2);
			b.rotar(-angulo);
			b.establecer_recorte(f.x, f.y, f.w, f.h);
			b.establecer_posicion(acc_espaciable_x()+(acc_espaciable_w()/2)-2,
				acc_espaciable_y()+(acc_espaciable_h()/2)-(f.h/2), 
				f.w, f.h);
		}
		break;
	}	

}

void Enemigo_tanque::turno(App_Interfaces::Contexto_turno_I& ct)
{
	float delta=ct.acc_delta();
	tiempo_proximo_disparo-=delta;

	auto v=obtener_vector_cartesiano_para(ct.acc_blanco());
	angulo=transformar_angulo_disparo(DLibH::Herramientas::angulo_360(v.angulo_grados()));
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
		auto g=Herramientas_proyecto::Generador_int(10, 30);
		auto gvel=Herramientas_proyecto::Generador_int(150, 300);
		int i=0, mp=g();
		while(i < mp)
		{
			auto g=Herramientas_proyecto::Generador_int(0, 359);
			auto v=Vector_2d::vector_unidad_para_angulo(g())*gvel();
			f.fabricar_chatarra(x, y, 3.0f, v);
			++i;
		}

		auto gtraza=Herramientas_proyecto::Generador_int(3, 5);
		auto gveltraza=Herramientas_proyecto::Generador_int(160, 200);
		auto gduracion=Herramientas_proyecto::Generador_int(40, 100);
		i=0;
		while(i < gtraza())
		{
			auto g=Herramientas_proyecto::Generador_int(0, 359);
			auto v=Vector_2d::vector_unidad_para_angulo(g())*gveltraza();
			float dur=(float)gduracion() / 100.0;
			f.fabricar_trazador_humo(x, y, dur, v);
			++i;
		}

		f.fabricar_explosion(x, y, 1.0f, v);
	}
	else
	{
		if(tiempo_proximo_disparo < 0.0f) 
		{
			tiempo_proximo_disparo=TIEMPO_PROXIMO_DISPARO_DEFECTO;

			//Calculamos el vector hasta el blanco.
			const auto v=obtener_vector_cartesiano_para(f.acc_blanco_disparo()) * 200.0f;

			float angulo_vector=DLibH::Herramientas::angulo_360(v.angulo_grados());

			if(validar_angulo_disparo(angulo_vector))
			{			
				float rad=DLibH::Herramientas::grados_a_radianes(angulo_vector);
				float canx=cos(rad)*8.f+dp.x;
				float cany=-(sin(rad)*8.f)+dp.y; //Negamos para convertir de cartesiano a pantalla...

				const auto dp=desplazamiento_origen_proyectil();

				f.fabricar_proyectil_normal_enemigo(acc_espaciable_cx()+canx, acc_espaciable_cy()+cany, 8, 8, v.a_pantalla(), 25.0);

				//TODO: Los concerns de audio están mezlados con el resto :(.
				insertar_reproducir(App_Audio::Info_audio_reproducir(
					App_Audio::Info_audio_reproducir::t_reproduccion::simple,
					App_Audio::Info_audio_reproducir::t_sonido::repetible,  
					App::Recursos_audio::rs_disparo, 127, 127));
			}
		}
	}
}

void Enemigo_tanque::efecto_colision(App_Interfaces::Efecto_colision_recogedor_I& er)
{
	er.recibir_impacto(2.5f);
}
