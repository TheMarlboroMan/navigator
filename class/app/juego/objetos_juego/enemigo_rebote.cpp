#include "enemigo_rebote.h"
#include "../../recursos.h"

using namespace App_Juego_ObjetoJuego;

Enemigo_rebote::Enemigo_rebote(float px, float py, float vel, tipos_rebote treb, App_Definiciones::direcciones dir)
	:Objeto_juego_I(),
	App_Juego::Actor_movil(px, py, W, H),
	velocidad(vel),
	rebote(treb),
	tiempo(0.0f)
{
	//TODO: Establecer vector según dirección.
	float vx=0.0f, vy=0.0f;

	switch(dir)
	{
		case App_Definiciones::direcciones::nada: break;
		case App_Definiciones::direcciones::arriba: 	vy=-1.0f; break;
		case App_Definiciones::direcciones::derecha: 	vx=1.0f; break;
		case App_Definiciones::direcciones::izquierda: 	vy=-1.0f; break;
		case App_Definiciones::direcciones::abajo: 	vy=1.0f; break;
	}

	establecer_vector(DLibH::Vector_2d(vx*vel, vy*vel));
}

void Enemigo_rebote::recibir_disparo(float potencia, App_Interfaces::Disparable_contexto_I& contexto)
{
	//No hace nada.
}
	
void Enemigo_rebote::turno(App_Interfaces::Contexto_turno_I& ct)
{
	float delta=ct.acc_delta();
	tiempo+=delta;

	//Moverse...
	auto v=acc_vector();
	desplazar_caja(v.x * delta, v.y * delta);

	//En caso de colisión o salir fuera del mundo, revertir.
	auto caja=copia_caja();
	auto cel=ct.celdas_en_caja(caja);
	if(ct.es_fuera_sala(caja) || cel.size())
	{
		if(cel.size())
		{
			if(v.x)
			{
				ajustar(*cel[0], v.x < 0 ? Actor_movil::posiciones_ajuste::izquierda : Actor_movil::posiciones_ajuste::derecha);
			}
			else if(v.y)
			{
				ajustar(*cel[0], v.y < 0 ? Actor_movil::posiciones_ajuste::arriba : Actor_movil::posiciones_ajuste::abajo);
			}			
		}

		cambiar_direccion();
	}
}


unsigned short int Enemigo_rebote::obtener_profundidad_ordenacion() const
{
	return 10;
}

unsigned int Enemigo_rebote::obtener_ciclos_representable() const
{
	return 1;
}

void Enemigo_rebote::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	using namespace App_Graficos;
	using namespace App_Definiciones;
	const auto& f=b.obtener_frame(animaciones::sprites, animaciones_sprites::enemigo_rebote, 0);

	//Se asume que todos los frames van mirando a la derecha.
	b.establecer_tipo(Bloque_transformacion_representable::tipos::tr_bitmap);
	b.establecer_alpha(255);
	b.establecer_recurso(App::Recursos_graficos::rt_juego);
	b.establecer_recorte(f.x, f.y, f.w, f.h);
	b.establecer_posicion(acc_espaciable_x()+f.desp_x, acc_espaciable_y()+f.desp_x, W, H);
	b.rotar(fmod(tiempo*100.0, 360));
}

float Enemigo_rebote::obtener_peso() const
{
	return 0.0f;
}

float Enemigo_rebote::obtener_max_velocidad_caida() const
{
	return 0.0f;
}

void Enemigo_rebote::callback_ajuste(float pos, posiciones_ajuste tipo)
{
	//No hacer nada...
}

void Enemigo_rebote::cambiar_direccion()
{
	auto v=acc_vector();
	switch(rebote)
	{
		case tipos_rebote::invertir:
			establecer_vector(DLibH::Vector_2d(-v.x, -v.y));
		break;
		case tipos_rebote::derecha:
			establecer_vector(DLibH::Vector_2d(-v.y, v.x));
		break;
		case tipos_rebote::izquierda:
			establecer_vector(DLibH::Vector_2d(v.y, -v.x));
		break;
	}
}

void Enemigo_rebote::efecto_colision(App_Interfaces::Efecto_colision_recogedor_I& er)
{
	er.recibir_impacto(2.5f);
}
