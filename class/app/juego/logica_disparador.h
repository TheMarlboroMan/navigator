#ifndef LOGICA_PROYECTILES_H
#define LOGICA_PROYECTILES_H

#include <memory>
#include <vector>
#include "objetos_juego/proyectil_normal.h"
#include "jugador.h"
#include "../interfaces/procesador_objetos_juego_i.h"
#include "../visitantes/visitante_disparador.h"

#include "objetos_juego/enemigo_basico.h"

/**
* Clase que controla la lógica de proyectiles de juego: insertar proyectiles
* del jugador, de los enemigos y de lo que fuera necesario.
* Actúa además como interface de "Procesador" y como visitante para 
* disparadores.
*/

namespace App_Juego
{

class Logica_disparador:
	public App_Interfaces::Procesador_objetos_juego_I,
	public App_Visitantes::Visitante_disparador
{
	///////////////////////
	//Interface pública:
	public:

				Logica_disparador(std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base> >&v, const Jugador& j);
	bool 			insertar_disparo_jugador(std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base> >&v);

	///////////////////////
	//Implementación de Procesdor_objetos_juego_I
	virtual void 		procesar(vector_oj v);

	/////////////////////
	//Implementación de Visitante_disparador.

	virtual void 		visitar(App_Juego_ObjetoJuego::Enemigo_basico&);

	///////////////////////
	//Propiedades:
	private:

	std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base> >& 	proyectiles_enemigos;
	const Jugador& jugador;
};

}

#endif
