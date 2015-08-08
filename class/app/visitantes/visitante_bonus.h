#ifndef VISITANTE_BONUS_H
#define VISITANTE_BONUS_H

namespace App_Juego_ObjetoJuego
{
class Bonus_tiempo;
class Bonus_salud;
}

namespace App_Visitantes
{
class Visitante_bonus
{
	public:

	virtual void visitar(App_Juego_ObjetoJuego::Bonus_tiempo&)=0;
	virtual void visitar(App_Juego_ObjetoJuego::Bonus_salud&)=0;
};
}

#endif
