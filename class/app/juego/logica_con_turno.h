#ifndef LOGICA_CON_TURNO_H
#define LOGICA_CON_TURNO_H

#include "../visitantes/visitante_con_turno.h"
#include "../colisiones/calculador_colisiones.h"
#include "objetos_juego/enemigo_basico.h"
#include "objetos_juego/enemigo_rebote.h"
#include "objetos_juego/proyectil_normal.h"
#include "jugador.h"

namespace App_Juego
{
class Logica_con_turno:
	public App_Visitantes::Visitante_con_turno
{
	///////////////////////
	//Interface pública.
	public:

					Logica_con_turno(const Jugador& j, const App_Niveles::Sala& s, float d);
	virtual void 			procesar(std::vector<std::shared_ptr<App_Interfaces::Con_turno_I>>&);

	///////////////////////
	//Implementación de Visitante_con_turno
	public:

	virtual void 			visitar(App_Juego_ObjetoJuego::Enemigo_basico&);
	virtual void 			visitar(App_Juego_ObjetoJuego::Enemigo_rebote&);
	virtual void 			visitar(App_Juego_ObjetoJuego::Proyectil_normal&);
	virtual void 			visitar(App_Juego_ObjetoJuego::Particula_fantasma&);
	virtual void 			visitar(App_Juego_ObjetoJuego::Particula_explosion&);

	///////////////////////
	//Propiedades privadas
	private:

	const Jugador&			jugador;
	const App_Niveles::Sala&	sala;
	float				delta;
};
}

#endif
