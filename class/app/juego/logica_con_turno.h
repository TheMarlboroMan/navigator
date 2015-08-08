#ifndef LOGICA_CON_TURNO_H
#define LOGICA_CON_TURNO_H

#include "../visitantes/visitante_con_turno.h"
#include "../interfaces/procesador_objetos_juego_i.h"
#include "../colisiones/calculador_colisiones.h"

#include "objetos_juego/enemigo_basico.h"
#include "objetos_juego/proyectil_normal.h"
#include "jugador.h"

namespace App_Juego
{
class Logica_con_turno:
	public App_Visitantes::Visitante_con_turno,
	public App_Interfaces::Procesador_objetos_juego_I
{
	///////////////////////
	//Interface pública.
	public:

					Logica_con_turno(const Jugador& j, const App_Niveles::Sala& s, float d);

	///////////////////////
	//Implementación de Visitante_con_turno
	public:

	virtual void 			visitar(App_Juego_ObjetoJuego::Enemigo_basico&);
	virtual void 			visitar(App_Juego_ObjetoJuego::Proyectil_normal&);

	///////////////////////
	//Implementación de Procesador_objetos_juego_I
	public:

	virtual void 			procesar(vector_oj v);

	///////////////////////
	//Propiedades privadas
	private:

	const Jugador&			jugador;
	const App_Niveles::Sala&	sala;
	float				delta;
};
}

#endif
