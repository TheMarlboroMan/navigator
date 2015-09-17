#ifndef OBSTACULO_GENERICO_H
#define OBSTACULO_GENERICO_H

#include "../actor.h"
#include "../../recursos.h"
#include "../../graficos/bloque_transformacion_representable.h"
#include "../../interfaces/objeto_juego_i.h"
#include "../../interfaces/representable_i.h"
#include "../../lectores/info_obstaculos_genericos.h"

/**
* Un objeto cuya única finalidad es ser solido y estar ahí, impidiendo el paso 
* del jugador y decorando un poco el mundo.
*/

namespace App_Juego_ObjetoJuego
{

class Obstaculo_generico:
	public App_Juego::Actor,
	public App_Interfaces::Objeto_juego_I,
	public App_Interfaces::Representable_I
{
	//////////////////
	//Interface pública

	public:

						Obstaculo_generico(float x, float y, int tipo, const App_Lectores::Info_obstaculos_genericos&);

	/////////////////
	//Implementación de Representable_I

	virtual unsigned int 			obtener_ciclos_representable()const;
	virtual unsigned short int 		obtener_profundidad_ordenacion()const;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;
	virtual bool				es_representable_borrar()const {return es_borrar();}

	/////////////////
	//Internas

	private:

	int					tipo;
	size_t					indice_animacion;

};

}

#endif
