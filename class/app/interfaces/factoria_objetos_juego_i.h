#ifndef FACTORIA_OBJETOS_JUEGO_I
#define FACTORIA_OBJETOS_JUEGO_I

#include <memory>

namespace App_Juego_ObjetoJuego
{
//class Proyectil_normal;
//class Bonus_salud;
class Bonus_tiempo;
}

namespace App_Interfaces
{
class Factoria_objetos_juego_I
{
	//////////////////////
	//Interface pública...
	public:

//	virtual void insertar(std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_normal>&)=0;
//	virtual void insertar(std::shared_ptr<App_Juego_ObjetoJuego::Bonus_salud>&)=0;
	virtual void insertar(std::shared_ptr<App_Juego_ObjetoJuego::Bonus_tiempo>&)=0;
};
}

#endif
