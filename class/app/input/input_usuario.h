#ifndef INPUT_USUARIO_H
#define INPUT_USUARIO_H

namespace App_Input
{

struct Input_usuario
{
	enum class t_estados {nada, down, pulsado};

	short int mov_horizontal;
	short int mov_vertical;
//	short int keyup_horizontal;
//	short int keyup_vertical;
	t_estados usar;
	t_estados recargar_escudo;
	t_estados estasis;

	Input_usuario():mov_horizontal(0), mov_vertical(0), /*keyup_horizontal(0), keyup_vertical(0), */
		usar(t_estados::nada), recargar_escudo(t_estados::nada), estasis(t_estados::nada)
	{}
};

}
#endif
