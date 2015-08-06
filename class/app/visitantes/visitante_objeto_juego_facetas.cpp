#include "visitante_objeto_juego_facetas.h"

using namespace App_Visitantes;

objeto_juego_facetas App_Visitantes::operator|(objeto_juego_facetas a, objeto_juego_facetas b)
{
	return static_cast<objeto_juego_facetas>(static_cast<int>(a) | static_cast<int>(b));
}

objeto_juego_facetas App_Visitantes::operator&(objeto_juego_facetas a, objeto_juego_facetas b)
{
	return static_cast<objeto_juego_facetas>(static_cast<int>(a) & static_cast<int>(b));
}
