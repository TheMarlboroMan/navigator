#ifndef INPUT_USUARIO_H
#define INPUT_USUARIO_H

namespace App_Input
{

struct Input_usuario
{
	short int mov_horizontal;
	short int mov_vertical;
	short int keyup_horizontal;
	short int keyup_vertical;

	Input_usuario():mov_horizontal(0), mov_vertical(0), keyup_horizontal(0), keyup_vertical(0)
	{}
};

}
#endif
