#ifndef BARRA_INDICADORA_H
#define BARRA_INDICADORA_H

#include <video/representacion/representacion_grafica/representacion_texto/representacion_texto_auto.h>
#include <video/representacion/representacion_primitiva/representacion_primitiva_caja/representacion_primitiva_caja.h>
#include <video/pantalla/pantalla.h>
#include <video/gestores/gestor_superficies.h>
#include <herramientas/herramientas_sdl/herramientas_sdl.h>

namespace App_Graficos
{

class Barra_indicadora
{
	typedef DLibV::Representacion_primitiva_caja_estatica 	rep_caja;
	typedef DLibV::Representacion_texto_auto_estatica	rep_txt;

	public:

								Barra_indicadora(int x, int y, int vmax, int vact, const std::string& nombre);
	void 							establecer_posicion(int, int);
	void 							establecer_dimensiones(unsigned int, unsigned int);
	void 							establecer_color(unsigned int r, unsigned int g, unsigned int b);
	void 							establecer_nombre(const std::string);
	void 							establecer_valor_max(int);
	void 							establecer_valor_actual(int);
	void							volcar(DLibV::Pantalla&);
	void							mostrar_cantidad() {txt_cantidad.hacer_visible();}
	void							ocultar_cantidad() {txt_cantidad.hacer_invisible();}
	void							establecer_caducidad(float v) {tiempo_vigencia=v;}
	void							caducar() {tiempo_vigencia=0.0;}
	bool							es_vigente() const {return tiempo_vigencia;}
	void							turno(float v);

	float							acc_valor_actual() const {return valor_actual;}

	private:

	static const unsigned int				W=100;
	static const unsigned int				H=10;
	static const unsigned int				R=255;
	static const unsigned int				G=255;
	static const unsigned int				B=255;
	
	rep_caja				 		caja;
	rep_txt					 		txt_nombre,
								txt_cantidad;
	std::string 						nombre;
	unsigned int						w_max;
	int 							valor_max;
	int 							valor_actual;
	float							tiempo_vigencia;
};

}

#endif
