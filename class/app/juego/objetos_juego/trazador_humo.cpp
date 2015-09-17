#include "trazador_humo.h"

using namespace App_Juego_ObjetoJuego;

const float Trazador_humo::max_tiempo_humo=0.05f;
const float Trazador_humo::duracion_humo=0.4f;

Trazador_humo::Trazador_humo(float x, float y, float tv, const DLibH::Vector_2d& v)
	:Objeto_juego_I(),
	Actor_movil(x, y, 1, 1),
	tiempo_vida(tv), tiempo_humo(max_tiempo_humo)
{
	establecer_vector(v);
}
	
float Trazador_humo::obtener_peso() const
{
	return 200.0f;
}

float Trazador_humo::obtener_max_velocidad_caida() const
{
	return 200.0f;
}

void Trazador_humo::callback_ajuste(float pos, posiciones_ajuste tipo)
{
	//Nada...
}

void Trazador_humo::turno(App_Interfaces::Contexto_turno_I& ct)
{
	const float delta=ct.acc_delta();
	tiempo_vida-=delta;
	tiempo_humo-=delta;
	desplazar(delta);
	accion_gravedad(delta);

	if(tiempo_vida <= 0.0f)
	{
		mut_borrar(true);
	}
}

void Trazador_humo::generar_objetos(App_Interfaces::Factoria_objetos_juego_I& f)
{
	if(tiempo_humo <= 0.0f)
	{
		tiempo_humo=max_tiempo_humo;
		auto gduracion=Herramientas_proyecto::Generador_int(10, 40);
		float dur=(float)gduracion() / 100.0;
		f.fabricar_humo(acc_espaciable_x(), acc_espaciable_y(), duracion_humo+dur);
	}
}
