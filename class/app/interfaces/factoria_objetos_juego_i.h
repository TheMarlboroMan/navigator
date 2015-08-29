#ifndef FACTORIA_OBJETOS_JUEGO_I
#define FACTORIA_OBJETOS_JUEGO_I

#include <memory>

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

	virtual void			fabricar_e_insertar_bonus_tiempo(float x, float y, float t)=0;

//	virtual void insertar(std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_normal>&)=0;
//	virtual void insertar(std::shared_ptr<App_Juego_ObjetoJuego::Bonus_salud>&)=0;
//	virtual void insertar(std::shared_ptr<App_Juego_ObjetoJuego::Bonus_tiempo>&)=0;
};
}

#endif
