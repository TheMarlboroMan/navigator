#ifndef VISITANTE_DISPARABLE_H
#define VISITANTE_DISPARABLE_H

namespace App_Juego_ObjetoJuego
{
class Enemigo_basico;
class Enemigo_rebote;
}

namespace App_Visitantes
{

class Visitante_disparable
{
	/////////////////////
	//Interface pública.
	public:

	virtual void visitar(App_Juego_ObjetoJuego::Enemigo_basico&)=0;
	virtual void visitar(App_Juego_ObjetoJuego::Enemigo_rebote&)=0;
};

}

#endif
