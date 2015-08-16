#ifndef VISITANTE_CON_TURNO_H
#define VISITANTE_CON_TURNO_H

namespace App_Juego_ObjetoJuego
{
class Enemigo_basico;
class Enemigo_rebote;
class Proyectil_normal;
}

namespace App_Visitantes
{
class Visitante_con_turno
{
	/////////////////////////
	//Interface pública.
	public:

	virtual void visitar(App_Juego_ObjetoJuego::Enemigo_basico&)=0;
	virtual void visitar(App_Juego_ObjetoJuego::Enemigo_rebote&)=0;
	virtual void visitar(App_Juego_ObjetoJuego::Proyectil_normal&)=0;
};
}

#endif
