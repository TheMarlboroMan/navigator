#ifndef VISITANTE_DISPARABLE_H
#define VISITANTE_DISPARABLE_H

namespace App_Juego_ObjetoJuego
{
class Enemigo_basico;
}

namespace App_Visitantes
{

class Visitante_disparable
{
	/////////////////////
	//Interface pública.
	public:

	virtual void visitar(App_Juego_ObjetoJuego::Enemigo_basico&)=0;
};

}

#endif
