#ifndef LOGICA_COLISIONABLE_H
#define LOGICA_COLISIONABLE_H

#include "../visitantes/visitante_colisionable.h"
#include "objetos_juego/enemigo_basico.h"
#include "objetos_juego/enemigo_rebote.h"
#include "objetos_juego/salida.h"
#include "jugador.h"

/**
* Clase que controla la lógica de recoger colisión con objetos de juego. Se
* entiende como lógica de colisión cualquier cosa que pueda pasar que no esté
* controlada en la "colisión con celdas".
*/

namespace App_Juego
{
class Logica_colisionable:
	public App_Visitantes::Visitante_colisionable
{
	/////////////////
	//Interface pública.
	public:

	Logica_colisionable(Jugador& j);
	virtual void 		procesar(std::vector<std::shared_ptr<App_Interfaces::Colisionable_I>>&);

	/////////////////
	//Implementación de Visitante_colisionable.
	public:

	virtual void 		visitar(App_Juego_ObjetoJuego::Enemigo_basico& b);
	virtual void 		visitar(App_Juego_ObjetoJuego::Enemigo_rebote& b);
	virtual void 		visitar(App_Juego_ObjetoJuego::Salida& b);

	/////////////////
	//Propiedades.
	private:

	Jugador& jugador;
};

}
#endif
