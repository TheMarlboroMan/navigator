#include "controlador_pausa.h"

Controlador_pausa::Controlador_pausa(Director_estados &DI, App_Juego_Automapa::Automapa& am)
	:Controlador_base(DI), 
	automapa(am),
	vista_automapa(21, 21),
	x_mapa(0), y_mapa(0) //Esta no será la posición final, por supuesto...
{
	vista_automapa.refrescar_vista(automapa, x_mapa, y_mapa);
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
			vista_automapa.refrescar_vista(automapa, x_mapa, y_mapa);
		}
		else if(input.es_input_down(Input::I_DERECHA)) 
		{
			++x_mapa;
			vista_automapa.refrescar_vista(automapa, x_mapa, y_mapa);
		}
		else if(input.es_input_down(Input::I_ARRIBA)) 
		{
			--y_mapa;
			vista_automapa.refrescar_vista(automapa, x_mapa, y_mapa);
		}
		else if(input.es_input_down(Input::I_ABAJO)) 
		{
			++y_mapa;
			vista_automapa.refrescar_vista(automapa, x_mapa, y_mapa);
		}
	}
}

void Controlador_pausa::dibujar(DLibV::Pantalla& pantalla)
{
	pantalla.limpiar(0, 0, 0, 255);
	representador.generar_vista(pantalla, vista_automapa.obtener_vista(50, 50, 14));
}

void Controlador_pausa::refrescar()
{
	vista_automapa.refrescar_vista(automapa, x_mapa, y_mapa);
}
