#ifndef VISITANTE_DISPARADOR_H
#define VISITANTE_DISPARADOR_H

/**
* Definición del modelo de visitante para cosas que puedan disparar.
*/

namespace App_Juego_ObjetoJuego
{
class Enemigo_basico;
}

namespace App_Visitantes
{
class Visitante_disparador
{
	/////////////////////
	//Interface pública.
	public:

	virtual void visitar(App_Juego_ObjetoJuego::Enemigo_basico&)=0;
};
}

#endif
