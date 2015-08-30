#ifndef FACTORIA_OBJETOS_JUEGO_I
#define FACTORIA_OBJETOS_JUEGO_I

#include <memory>
#include <herramientas/vector_2d/vector_2d.h>
#include <herramientas/caja/caja.h>

#include "../definiciones/definiciones.h"

namespace App_Interfaces
{
	class Espaciable;
}

namespace App_Juego_ObjetoJuego
{
	class Objeto_juego_I;
}

namespace App_Interfaces
{
class Factoria_objetos_juego_I
{
	//////////////////////
	//Interface pública...
	public:

	virtual				~Factoria_objetos_juego_I();

	virtual void			fabricar_bonus_tiempo(float x, float y, float t)=0;
	virtual void			fabricar_bonus_salud(float x, float y, float t)=0;

	virtual void			fabricar_proyectil_normal_enemigo(float x, float y, int w, int h, const DLibH::Vector_2d& v, float pot)=0;

	virtual void			fabricar_chispa(float x, float y, float tv, const DLibH::Vector_2d&)=0;
	virtual void			fabricar_explosion(float x, float y, float tv, const DLibH::Vector_2d&)=0;
	virtual void			fabricar_chatarra(float x, float y, float tv, const DLibH::Vector_2d&)=0;
	virtual void			fabricar_fantasma(float x, float y, float tv, float ve, App_Definiciones::direcciones direccion, int recurso, const DLibH::Caja<int, int>& recorte)=0;

	virtual const App_Interfaces::Espaciable& 	acc_blanco_disparo() const=0;
};
}

#endif
