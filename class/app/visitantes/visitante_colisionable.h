#ifndef VISITANTE_COLISIONABLE_H
#define VISITANTE_COLISIONABLE_H

namespace App_Juego_ObjetoJuego
{
class Enemigo_basico;
class Salida;
}

namespace App_Visitantes
{
class Visitante_colisionable
{
	/////////////////////////
	//Interface pública.
	public:

	virtual void visitar(App_Juego_ObjetoJuego::Enemigo_basico&)=0;
	virtual void visitar(App_Juego_ObjetoJuego::Salida&)=0;
};
}

#endif
