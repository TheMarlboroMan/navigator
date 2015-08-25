#ifndef BLOQUE_TRANSFORMACION_REPRESENTABLE_H
#define BLOQUE_TRANSFORMACION_REPRESENTABLE_H

#include <libDan2.h>

namespace App_Graficos
{

struct Bloque_transformacion_representable
{
	///////////////////////////////////
	// Definiciones...

	enum class tipos{
		TR_BITMAP=1,
		TR_GRUPO_DINAMICO=2,
		TR_GRUPO_ESTATICO=3
	};

	///////////////////////////////////
	// Propiedades

	private:

	DLibV::Representacion_bitmap_dinamica rep_bmp;
	DLibV::Representacion_agrupada_dinamica rep_agr_din;
	DLibV::Representacion_agrupada_estatica rep_agr_est;
	DLibV::Representacion * rep;
	tipos tipo_actual;
	bool visible;
	
	///////////////////////////////////
	// Interfaz pública

	public:

	Bloque_transformacion_representable()
		:rep_bmp(), 
		rep_agr_din(true),
		rep_agr_est(true),
		rep(&rep_bmp),
		tipo_actual(tipos::TR_BITMAP),
		visible(true)
	{
		rep_agr_din.imponer_alpha();
		rep_agr_din.imponer_modo_blend();

		rep_agr_est.imponer_alpha();
		rep_agr_est.imponer_modo_blend();
	}

	~Bloque_transformacion_representable()
	{
		rep_agr_din.vaciar_grupo();
		rep_agr_est.vaciar_grupo();
	}

	bool es_visible() const {return visible;}

	void establecer_recorte(unsigned int x, unsigned int y, unsigned int w, unsigned int h) 
	{
		rep->establecer_recorte(x, y, w, h);	
	}

	void establecer_posicion(unsigned int x, unsigned int y, unsigned int w, unsigned int h) 
	{
		rep->establecer_posicion(x, y, w, h);
	}

	SDL_Rect acc_posicion() const 
	{
		return rep->acc_posicion();
	}

	void establecer_tipo(tipos t)
	{
		switch(t)
		{
			case tipos::TR_BITMAP: 
				tipo_actual=tipos::TR_BITMAP;
				rep_bmp.reiniciar_transformacion();
//				rep_bmp.establecer_mod_color(255,255,255);
				rep=&rep_bmp;
			break;

			case tipos::TR_GRUPO_DINAMICO:
				rep_agr_din.vaciar_grupo();
				tipo_actual=tipos::TR_GRUPO_DINAMICO;
				rep=&rep_agr_din;
			break;

			case tipos::TR_GRUPO_ESTATICO:
				rep_agr_est.vaciar_grupo();
				tipo_actual=tipos::TR_GRUPO_ESTATICO;
				rep=&rep_agr_est;
			break;
		}

		establecer_alpha(255);
		establecer_blend(DLibV::Representacion::BLEND_ALPHA);
		establecer_mod_color(255, 255, 255);
		visible=true;
	}

	void ocultar()
	{
		visible=false;
	}

	void establecer_alpha(unsigned int v) 
	{
		if(v > 255) v=255;
		rep->establecer_alpha(v);
	}

	void establecer_blend(unsigned int v) {rep->establecer_modo_blend(v);}
	void establecer_mod_color(unsigned int r, unsigned int g, unsigned int b) {rep->establecer_mod_color(r, g, b);}

	///////////////////
	// Metodos para manipular el grupo de representaciones...

	void insertar_en_grupo(DLibV::Representacion * r) 
	{
		switch(tipo_actual)
		{
			case tipos::TR_BITMAP: 	break;
			case tipos::TR_GRUPO_DINAMICO:	rep_agr_din.insertar_representacion(r);	break;
			case tipos::TR_GRUPO_ESTATICO:	rep_agr_est.insertar_representacion(r);	break;
		}
	}

	///////////////////
	// Métodos para manipular la representación de bitmap...

	void invertir_horizontal(bool v) {rep_bmp.transformar_invertir_horizontal(v);}
	void invertir_vertical(bool v) {rep_bmp.transformar_invertir_vertical(v);}
	void rotar(float v) {rep_bmp.transformar_rotar(v);}
	void especificar_centro_rotacion(float x, float y) {rep_bmp.transformar_centro_rotacion(x, y);}

	void establecer_recurso(unsigned int i) //Por defecto establece el recorte al tamaño del recurso.
	{
		if(!DLibV::Gestor_texturas::comprobar(i)) LOG<<"SOLICITADO RECURSO "<<i<<", NO EXISTENTE"<<std::endl;
		else rep_bmp.establecer_textura(DLibV::Gestor_texturas::obtener(i));
	}
/*
	void establecer_recurso_sin_recortar(unsigned int i)
	{
		if(!DLibV::Gestor_texturas::comprobar(i)) LOG<<"SOLICITADO RECURSO "<<i<<", NO EXISTENTE"<<std::endl;
		else rep_bmp.establecer_textura_sin_recortar(DLibV::Gestor_texturas::obtener(i));
	}
*/
	//Establece un recurso que no tiene porqué estar en el gestor.	
	void establecer_textura_manual(DLibV::Textura * r) {rep_bmp.establecer_textura(r);}

	friend class Representador;
};

}

#endif
