#include "controlador_pausa.h"

Controlador_pausa::Controlador_pausa(Director_estados &DI, App_Juego_Automapa::Automapa& am)
	:Controlador_base(DI), 
	automapa(am),
	vista_automapa(21, 21),
	x_mapa(0), y_mapa(0) //Esta no será la posición final, por supuesto...
{
	automapa.refrescar_vista(x_mapa, y_mapa);
}

void Controlador_pausa::preloop(Input_base& input, float delta)
{

}

void Controlador_pausa::postloop(Input_base& input, float delta)
{

}

void Controlador_pausa::loop(Input_base& input, float delta)
{
	if(input.es_senal_salida() || input.es_input_down(Input::I_ESCAPE))
	{
		abandonar_aplicacion();
	}
	else
	{
		if(input.es_input_down(Input::I_INTERCAMBIAR_PANTALLA_PAUSA))
		{
			solicitar_cambio_estado(Director_estados::t_estados::juego);
			return;
		}

		//TODO: Mejorar: controlar que cuando salimos del mapa no se vuelva y explote!!!!.

		if(input.es_input_down(Input::I_IZQUIERDA)) 
		{
			--x_mapa;
			vista_automapa.refrescar_vista(x_mapa, y_mapa);
		}
		else if(input.es_input_down(Input::I_DERECHA)) 
		{
			++x_mapa;
			vista_automapa.refrescar_vista(x_mapa, y_mapa);
		}
		else if(input.es_input_down(Input::I_ARRIBA)) 
		{
			--y_mapa;
			vista_automapa.refrescar_vista(x_mapa, y_mapa);
		}
		else if(input.es_input_down(Input::I_ABAJO)) 
		{
			++y_mapa;
			vista_automapa.refrescar_vista(x_mapa, y_mapa);
		}
	}
}

void Controlador_pausa::dibujar(DLibV::Pantalla& pantalla)
{
	pantalla.limpiar(0, 0, 0, 255);
	//TODO TODO TODO
	//representador.generar_vista(pantalla, automapa.obtener_vista(200, 200, 7));
}

void Controlador_pausa::centrar_mapa(const std::tuple<int, int>& t)
{
	x_mapa=std::get<0>(t);
	y_mapa=std::get<1>(t);
	automapa.establecer_posicion_jugador(x_mapa, y_mapa);
	//TODO TODO TODO TODO TODO...
	//automapa.refrescar_vista(x_mapa, y_mapa);
}
