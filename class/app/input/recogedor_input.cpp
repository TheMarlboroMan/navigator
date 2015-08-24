#include "recogedor_input.h"

using namespace App_Input;

Input_usuario Recogedor_input::recoger_input_usuario(Input_base& input) const
{
	auto proc=[&input](Input_usuario::t_estados& e, int t)
	{
		if(input.es_input_down(t)) 		e=Input_usuario::t_estados::down;
		else if(input.es_input_pulsado(t)) 	e=Input_usuario::t_estados::pulsado;
	};

	Input_usuario resultado;

	proc(resultado.usar, Input::I_USAR_SELECCION);
	proc(resultado.recargar_escudo, Input::I_RECARGA_ESCUDO);
	proc(resultado.estasis, Input::I_ESTASIS);

	if(input.es_input_pulsado(Input::I_DERECHA)) resultado.mov_horizontal=1;
	else if(input.es_input_pulsado(Input::I_IZQUIERDA)) resultado.mov_horizontal=-1;
//	else if(input.es_input_up(Input::I_DERECHA)) resultado.keyup_horizontal=1;
//	else if(input.es_input_up(Input::I_IZQUIERDA)) resultado.keyup_horizontal=-1;

	if(input.es_input_pulsado(Input::I_ARRIBA)) resultado.mov_vertical=-1;
	else if(input.es_input_pulsado(Input::I_ABAJO)) resultado.mov_vertical=1;
//	else if(input.es_input_pulsado(Input::I_ARRIBA)) resultado.keyup_vertical=-1;
//	else if(input.es_input_pulsado(Input::I_ABAJO)) resultado.keyup_vertical=1;

	return resultado;
}
