#include "proyectil_rayo_estatico.h"

using namespace App_Juego_ObjetoJuego;

Proyectil_rayo_estatico::Proyectil_rayo_estatico(float x, float y, int w, int h, float potencia)
	:Proyectil_base(x, y, w, h),
	longitud(0),
	tiempo_vida(0.5f)
{
	mut_potencia(potencia);
	establecer_vector(DLibH::Vector_2d(0.f, 0.f));
	longitud=acc_espaciable_w() > acc_espaciable_h() ? 
			acc_espaciable_w() / App_Definiciones::definiciones::dim_celda : 
			acc_espaciable_h() / App_Definiciones::definiciones::dim_celda;
}

void Proyectil_rayo_estatico::colisionar_con_nivel()
{
	//Do nothing :D.
}

void Proyectil_rayo_estatico::colisionar_con_enemigo()
{
	//Do nothing :D.
}

void Proyectil_rayo_estatico::colisionar_con_jugador()
{
	//Do nothing :D.
}

void Proyectil_rayo_estatico::generar_objetos(App_Interfaces::Factoria_objetos_juego_I& foj)
{
	//Do... nothing. Esto es para las chispas.
}

void Proyectil_rayo_estatico::turno(App_Interfaces::Contexto_turno_I& ct)
{
	tiempo_vida-=ct.acc_delta();
	if(tiempo_vida <= 0.0f)
	{
		mut_borrar(true);
	}
	else
	{

	}
}

unsigned int Proyectil_rayo_estatico::obtener_ciclos_representable()const
{
	return 2;
}

unsigned short int Proyectil_rayo_estatico::obtener_profundidad_ordenacion()const
{
	return 40;
}

void Proyectil_rayo_estatico::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
{
	using namespace App_Graficos;
/*
	switch(b.acc_ciclo())
	{
		case 1:
			b.establecer_tipo(Bloque_transformacion_representable::tipos::tr_primitiva_caja);
			b.posicion_caja(acc_espaciable_x(), acc_espaciable_y(), acc_espaciable_w(), acc_espaciable_h());
			b.color_caja(128, 0, 0);
		break;
		case 2:
			b.establecer_tipo(Bloque_transformacion_representable::tipos::tr_primitiva_puntos);
			b.color_puntos(192, 0, 0);

			auto px=Herramientas_proyecto::Generador_int(acc_espaciable_x(), acc_espaciable_fx()),
				py=Herramientas_proyecto::Generador_int(acc_espaciable_y(), acc_espaciable_fy());
			int p=puntos_por_longitud * longitud;
			while(p--) b.insertar_punto(px(), py());
		break;
	}
*/
	b.establecer_alpha(192);
}
