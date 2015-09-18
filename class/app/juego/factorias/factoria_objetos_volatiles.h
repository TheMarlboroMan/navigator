#ifndef FACTORIA_OBJETOS_VOLATILES_H
#define FACTORIA_OBJETOS_VOLATILES_H

#include <stdexcept>
#include <vector>
#include <string>
#include <herramientas/herramientas/herramientas.h>
#include <herramientas/vector_2d/vector_2d.h>

#include "../contenedores/contenedor_volatiles.h"
#include "../objetos_juego/particula_chispa.h"
#include "../objetos_juego/particula_explosion.h"
#include "../objetos_juego/particula_chatarra.h"
#include "../objetos_juego/particula_fantasma_jugador.h"
#include "../objetos_juego/particula_fantasma_bonus_tiempo.h"
#include "../objetos_juego/particula_fantasma_bonus_salud.h"
#include "../objetos_juego/particula_humo.h"
#include "../objetos_juego/proyectil_normal.h"
#include "../objetos_juego/proyectil_rayo_estatico.h"


namespace App_Juego_Factorias
{

class Factoria_objetos_volatiles
{
	///////////////////////
	// Interface pública...

	public:

	//TODO: Quizás sean unique_ptr...
	std::shared_ptr<App_Juego_ObjetoJuego::Particula_chispa>	crear_chispa(float x, float y, float tv, const DLibH::Vector_2d& v);
	std::shared_ptr<App_Juego_ObjetoJuego::Particula_explosion>	crear_explosion(float x, float y, float tv, const DLibH::Vector_2d& v);
	std::shared_ptr<App_Juego_ObjetoJuego::Particula_chatarra>	crear_chatarra(float x, float y, float tv, const DLibH::Vector_2d& v);
	std::shared_ptr<App_Juego_ObjetoJuego::Particula_fantasma_jugador>	crear_fantasma_jugador(float x, float y, float tv, float ve, App_Definiciones::direcciones direccion);
	std::shared_ptr<App_Juego_ObjetoJuego::Particula_fantasma_bonus_tiempo>	crear_fantasma_bonus_tiempo(float x, float y, float tv, float ve);
	std::shared_ptr<App_Juego_ObjetoJuego::Particula_fantasma_bonus_salud>	crear_fantasma_bonus_salud(float x, float y, float tv, float ve);
	std::shared_ptr<App_Juego_ObjetoJuego::Particula_humo>		crear_humo(float x, float y, float tv);
	std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_normal>	crear_proyectil_normal(float x, float y, int w, int h, const DLibH::Vector_2d& v, float pot);
	std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_rayo_estatico>	crear_proyectil_rayo_estatico(float x, float y, int w, int h, float pot);
	std::shared_ptr<App_Juego_ObjetoJuego::Trazador_humo>		crear_trazador_humo(float x, float y, float tv, const DLibH::Vector_2d& v);

	///////////////////////
	// Internas...

	private:


};

}

#endif
