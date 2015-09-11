#include "jugador.h"

using namespace App_Juego;
using namespace App_Graficos;
using namespace App;

const float Jugador::ACELERACION_VERTICAL_SEGUNDO=200.0;
const float Jugador::ACELERACION_HORIZONTAL_SEGUNDO=300.0;
const float Jugador::DECELERACION_HORIZONTAL_SEGUNDO=350.0;
const float Jugador::MAXIMA_VELOCIDAD_HORIZONTAL=200.0;
const float Jugador::MAXIMA_VELOCIDAD_VERTICAL=150.0;
const float Jugador::MAXIMA_VELOCIDAD_CAIDA=150.0;
const float Jugador::VELOCIDAD_MINIMA_IMPACTO=100.0;
const float Jugador::ESCUDO_RECUPERADO_POR_SEGUNDO=25.0f;
const float Jugador::ENERGIA_RECUPERADA_POR_SEGUNDO=25.0f;
const float Jugador::ENERGIA_ESTASIS_POR_SEGUNDO=25.0f;
const float Jugador::TIEMPO_COOLOFF_ENERGIA=1.5f;
const float Jugador::UMBRAL_DETENCION_ESTASIS=1.0f;
const float Jugador::FACTOR_DETENCION_ESTASIS=1.2f;
const float Jugador::VALOR_GRAVEDAD=1.0f;
const float Jugador::TIEMPO_COMPLETAR_ATERRIZAJE=1.2f;
const float Jugador::VELOCIDAD_MOD_COLOR=500.0f;

Jugador::Jugador(float x, float y)
	:Actor_movil(x, y, W, H),
	mod_color{255.0, 255.0, 255.0},
	posicion_anterior(copia_caja()),
	salud(MAX_SALUD), energia(MAX_ENERGIA), 
	escudo(MAX_ESCUDO), cooloff_energia(0.0f),
	tiempo_aterrizado(0.0),
//	TREC("data/recortes/jugador.dat"),	
	direccion(App_Definiciones::direcciones::derecha)
{
	establecer_vector(100.0, Movil::t_vector::V_X);
}

Jugador::~Jugador()
{

}

void Jugador::callback_ajuste(float pos, Actor_movil::posiciones_ajuste tipo)
{
	auto func=[this](float v, Movil::t_vector tv)
	{
		float fv=abs(v);
		float nv=0.0;

		if(fv >= VELOCIDAD_MINIMA_IMPACTO) 
		{
			recibir_impacto(fv);
			nv=-v / 2.0;
		}

		establecer_vector(nv, tv);
	};

	switch(tipo)
	{
		case Actor_movil::posiciones_ajuste::arriba:
		case Actor_movil::posiciones_ajuste::abajo:
		{
			func(acc_vector_y(), Movil::t_vector::V_Y);
		}	
		break;
		case Actor_movil::posiciones_ajuste::izquierda:
		case Actor_movil::posiciones_ajuste::derecha:
		{
			func(acc_vector_x(), Movil::t_vector::V_X);
		}
		break;
		case Actor_movil::posiciones_ajuste::nada:
			//Noop.
		break;
	}
}

/**
* @param float val : valor del impacto recibido, el vector de colisión, por ejemplo.
*/

void Jugador::recibir_impacto(float val)
{
	if(val < escudo)
	{
		escudo-=val;
		salud-=val / 4;
	}
	else
	{
		float dif=val-escudo;
		escudo=0.0;
		salud-=dif;
	}

	if(escudo < 0.0) escudo=0.0;
	if(salud < 0.0) salud=0.0;

	mod_color.r=escudo ? 0.0 : 255.0;
	mod_color.g=escudo ? 0.0 : 0.0;
	mod_color.b=escudo ? 255.0 : 0.0;

	/*
	* Un pequeño hack: el sonido golpe_jugador apunta al mismo wav pero
	* si sólo lo usa el jugador será único (para modos de single player)
	* y no volverá a sonar mientras esté activo.
	*/

	insertar_reproducir(App_Audio::Info_audio_reproducir(
		App_Audio::Info_audio_reproducir::t_reproduccion::simple,
		App_Audio::Info_audio_reproducir::t_sonido::unico,  
		App::Recursos_audio::rs_golpe_jugador, 127, 127));
}

void Jugador::transformar_bloque(Bloque_transformacion_representable &b) const
{
	using namespace App_Definiciones;
	const auto& f=b.obtener_frame(animaciones::sprites, animaciones_sprites::jugador, 0);

	//Se asume que todos los frames van mirando a la derecha.
	b.establecer_tipo(Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(255);
	b.establecer_recurso(Recursos_graficos::rt_juego);
	b.establecer_recorte(f.x, f.y, f.w, f.h);
		//TODO: De dónde salen esos dos números fijos???????????????????
	b.establecer_posicion(acc_espaciable_x()+f.desp_x, acc_espaciable_y()+f.desp_y, 27, 16);
	b.invertir_horizontal(direccion==App_Definiciones::direcciones::izquierda);
	b.establecer_mod_color(mod_color.r, mod_color.g, mod_color.b);
}

void Jugador::turno(float delta)
{
	using namespace App_Input;

	posicion_anterior=copia_caja();

	//TODO: Meter el tema de mod color como otro objeto de forma que podamos 
	//reutilizarlo en otros objetos del juego. Podríamos poner la velocidad
	//en el constructor, por ejemplo.

	auto proc_color=[delta](float& c)
	{
		c+=delta * VELOCIDAD_MOD_COLOR;
		if(c > 255.0) c=255.0;
	};

	proc_color(mod_color.r);
	proc_color(mod_color.g);
	proc_color(mod_color.b);

	//Recuperación de la energía.
	if(cooloff_energia)
	{
		cooloff_energia-=delta;
		if(cooloff_energia <= 0.0f) cooloff_energia=0.0f;
	}
	else if(energia < MAX_ENERGIA )
	{
		float factor=es_aterrizado() ? ENERGIA_RECUPERADA_POR_SEGUNDO * 4.0 : ENERGIA_RECUPERADA_POR_SEGUNDO;
		energia+=(delta * factor);
		if(energia > MAX_ENERGIA) energia=MAX_ENERGIA;
	}

	//Recuperación de escudo.
	float consumo_escudo=ENERGIA_ESTASIS_POR_SEGUNDO * delta;

	//TODO: No me gusta el planteamiento que va mezclando las consideraciones
	//de sonido con la lógica interna.

	if(input.recargar_escudo != Input_usuario::t_estados::nada)
	{
		if(energia >= consumo_escudo && escudo < MAX_ESCUDO)
		{
			escudo+=(delta * ESCUDO_RECUPERADO_POR_SEGUNDO);
			if(escudo > MAX_ESCUDO) escudo=MAX_ESCUDO;
			consumir_energia(consumo_escudo);

			if(input.recargar_escudo==Input_usuario::t_estados::down)
			{
				insertar_reproducir(App_Audio::Info_audio_reproducir(
						App_Audio::Info_audio_reproducir::t_reproduccion::simple,
						App_Audio::Info_audio_reproducir::t_sonido::unico,
						App::Recursos_audio::rs_recargar_escudo, 127, 127));
			}
		}
	}

	//Movimiento y estasis.
	float consumo_estasis=ENERGIA_ESTASIS_POR_SEGUNDO * delta;

	senales.crear_fantasma=false;

	if(input.estasis!=Input_usuario::t_estados::nada && energia >= consumo_estasis)
	{
		auto v=acc_vector();
		float fx=fabs(v.x) <= UMBRAL_DETENCION_ESTASIS ? 0.0f : (v.x / FACTOR_DETENCION_ESTASIS);
		float fy=fabs(v.y) <= UMBRAL_DETENCION_ESTASIS ? 0.0f : (v.y / FACTOR_DETENCION_ESTASIS);
		establecer_vector(DLibH::Vector_2d(fx, fy));
		consumir_energia(consumo_estasis);

		if(input.estasis==Input_usuario::t_estados::down)
		{
			insertar_reproducir(App_Audio::Info_audio_reproducir(
					App_Audio::Info_audio_reproducir::t_reproduccion::simple,
					App_Audio::Info_audio_reproducir::t_sonido::unico,
					App::Recursos_audio::rs_estasis, 127, 127));

			senales.crear_fantasma=true;
		}
	}
	else
	{
		accion_gravedad(delta, VALOR_GRAVEDAD);

		//Frenada o aceleración.
		if(input.mov_horizontal)
		{
			float v=acc_vector_x();
			v+=(delta * ACELERACION_HORIZONTAL_SEGUNDO) * input.mov_horizontal;

			if(v > MAXIMA_VELOCIDAD_HORIZONTAL) v=MAXIMA_VELOCIDAD_HORIZONTAL;
			else if(v < -MAXIMA_VELOCIDAD_HORIZONTAL) v=-MAXIMA_VELOCIDAD_HORIZONTAL;

			establecer_vector(v, Movil::t_vector::V_X);

			if(input.mov_horizontal < 0) direccion=App_Definiciones::direcciones::izquierda;
			else direccion=App_Definiciones::direcciones::derecha;

		}
		else
		{
			float v=abs(acc_vector_x());
			v-=(delta * ACELERACION_HORIZONTAL_SEGUNDO);
			if(v < 0.0) v=0;

			//Aproximarse al cero.
			float vr=acc_vector_x();
			if(vr > 0.0) establecer_vector(v, Movil::t_vector::V_X);
			else if(vr < 0.0) establecer_vector(-v, Movil::t_vector::V_X);	
		}

		if(input.mov_vertical)
		{
			float v=acc_vector_y();
			v+=(delta * ACELERACION_VERTICAL_SEGUNDO) * input.mov_vertical;

			if(v > 0.0 && v > MAXIMA_VELOCIDAD_VERTICAL) v=MAXIMA_VELOCIDAD_VERTICAL;
			else if(v < 0.0 && v < -MAXIMA_VELOCIDAD_CAIDA) v=-MAXIMA_VELOCIDAD_CAIDA;

			establecer_vector(v, Movil::t_vector::V_Y);
		}
	}
}

/**
* Esta es la función que usamos para restar energía de donde sea. Activa el 
* cooloff de energía. Ojo, no se comprueba si tienes energía suficiente!!!!.
*/

void Jugador::consumir_energia(float c)
{
	energia-=c;
	cooloff_energia=TIEMPO_COOLOFF_ENERGIA;
}

void Jugador::sumar_salud(float v)
{
	salud+=v;
	if(salud > MAX_SALUD) salud=MAX_SALUD;
}

bool Jugador::disparar()
{
	if(energia >= 10.0f)
	{
		consumir_energia(10.0f);
		sumar_vector(direccion==App_Definiciones::direcciones::izquierda ? 30.0 : -30.0, Movil::t_vector::V_X);
		
		insertar_reproducir(App_Audio::Info_audio_reproducir(
					App_Audio::Info_audio_reproducir::t_reproduccion::simple, 
					App_Audio::Info_audio_reproducir::t_sonido::repetible, 
					App::Recursos_audio::rs_disparo, 127, 127));

		return true;
	}

	return false;
}

void Jugador::contabilizar_tiempo_aterrizado(float delta)
{
	if(!delta)
	{
		tiempo_aterrizado=0.0;
	}
	else 
	{
		tiempo_aterrizado+=delta;
		if(tiempo_aterrizado > TIEMPO_COMPLETAR_ATERRIZAJE) tiempo_aterrizado=TIEMPO_COMPLETAR_ATERRIZAJE;
	}
}

bool Jugador::es_aterrizado() const 
{
	const auto& v=acc_vector();
	return tiempo_aterrizado >= TIEMPO_COMPLETAR_ATERRIZAJE && !v.x && !v.y;
}

void Jugador::generar_objetos(App_Interfaces::Factoria_objetos_juego_I& f)
{
	if(senales.crear_fantasma)
	{
//TODO: EEERRROR.... No tenemos acceso a los frames desde aquí!!!!!...
//		using namespace App_Definiciones;
//		const auto& frame=b.obtener_frame(animaciones::sprites, animaciones_sprites::jugador, 0);

//		f.fabricar_fantasma(					
//			acc_espaciable_x(), acc_espaciable_y(), 1.0f, 20.0f, direccion,
//			App::Recursos_graficos::rt_juego, DLibH::Caja<int, int>(frame.x, frame.y, frame.w, frame.h));
	}
}
