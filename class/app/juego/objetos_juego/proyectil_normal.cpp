#include "proyectil_normal.h"
#include "../../recursos.h"

using namespace App_Juego_ObjetoJuego;

const float Proyectil_normal::FACTOR_DEBILITAR=9.0f;

Proyectil_normal::Proyectil_normal(const Propiedades_proyectil& pp)
	:Proyectil_base(pp.x, pp.y, pp.w, pp.h),
	color(colores::rojo), cantidad_chispas(0), tv_chispas(0.0f)
{

}

Proyectil_normal::Proyectil_normal(float x, float y, int w, int h, const DLibH::Vector_2d& v, float potencia, App_Juego_ObjetoJuego::Proyectil_normal::colores color)
	:Proyectil_base(x, y, w, h),
	color(color)
{
	mut_potencia(potencia);
	establecer_vector(v);
}

void Proyectil_normal::turno(float delta)
{
	float p=acc_potencia();
	mut_potencia(p - (delta * FACTOR_DEBILITAR));

	if(acc_potencia() < 0.0f) 
	{
		mut_potencia(0.0f);
		mut_borrar(true);
	}
	else
	{
		const auto& v=acc_vector();
		desplazar_caja(v.x * delta, v.y * delta); 
	}
}

unsigned short int Proyectil_normal::obtener_profundidad_ordenacion()const
{
	return 40;
}

void Proyectil_normal::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	using namespace App_Graficos;
	using namespace App;

//	unsigned int alpha=(acc_potencia() * 255.0f) / acc_potencia_original();

	b.establecer_tipo(Bloque_transformacion_representable::tipos::tr_bitmap);
//	b.establecer_alpha(alpha);
	b.establecer_recurso(Recursos_graficos::rt_defecto);
	
	switch(color)
	{
		case colores::rojo: b.establecer_recorte(32, 16, acc_espaciable_w(), acc_espaciable_h()); break;
		case colores::azul: b.establecer_recorte(40, 16, acc_espaciable_w(), acc_espaciable_h()); break;
	}

	b.establecer_posicion(acc_espaciable_x(), acc_espaciable_y(), acc_espaciable_w(), acc_espaciable_h());
}

void Proyectil_normal::colisionar_con_nivel()
{
	mut_borrar(true);
	cantidad_chispas=5;
	tv_chispas=0.3f;

	insertar_reproducir(App_Audio::Info_audio_reproducir(
		App_Audio::Info_audio_reproducir::t_reproduccion::simple,
		App_Audio::Info_audio_reproducir::t_sonido::repetible,  
		App::Recursos_audio::rs_disparo_pared, 64, 127));
}

void Proyectil_normal::colisionar_con_enemigo()
{
	mut_borrar(true);
	cantidad_chispas=15;
	tv_chispas=0.3f;
}

void Proyectil_normal::colisionar_con_jugador()
{
	mut_borrar(true);
	cantidad_chispas=25;
	tv_chispas=0.6f;
}

void Proyectil_normal::generar_objetos(App_Interfaces::Factoria_objetos_juego_I& f)
{
	if(cantidad_chispas)
	{
		auto ggrad=HerramientasProyecto::Generador_int(-30, 30);
		auto gvel=HerramientasProyecto::Generador_int(150, 300);
		int i=0;

		float x=acc_espaciable_x()+(acc_espaciable_w()/2);
		float y=acc_espaciable_y()+(acc_espaciable_w()/2);

		while(i < cantidad_chispas)
		{
			auto v=DLibH::Vector_2d::vector_unidad_para_angulo(acc_vector().angulo_grados()+ggrad()-90.0f)*gvel();
			v.x=v.x-1;
			v.y=v.y-1;
			f.fabricar_chispa(x, y, tv_chispas, v);
			++i;
		}
	}
}
