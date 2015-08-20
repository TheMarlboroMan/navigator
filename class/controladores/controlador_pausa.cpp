#include "controlador_pausa.h"

Controlador_pausa::Controlador_pausa(Director_estados &DI, App_Niveles::Mapa& m)
	:Controlador_base(DI), 
	mapa(m), 
	automapa(21, 21),
	x_mapa(0), y_mapa(0)
{
	struct llamable_salas
	{
		struct info
		{
			int x, y;
			App_Definiciones::direcciones dir;
			info(int px, int py, App_Definiciones::direcciones pd)
				:x(px), y(py), dir(pd)
			{} 
		};

		std::vector<info> v;

		void operator()(const App_Niveles::Sala& s)
		{
			v.push_back(info(s.acc_x(), s.acc_y(), s.acc_direcciones_entradas()) );
		}
	}ls;

	automapa.inicializar(mapa.acc_w(), mapa.acc_h());
	mapa.para_cada_sala(ls);
	for(const auto& i : ls.v) automapa.configurar(i.x, i.y, i.dir);

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

		if(input.es_input_down(Input::I_IZQUIERDA)) 
		{
			--x_mapa;
			automapa.refrescar_vista(x_mapa, y_mapa);
		}
		else if(input.es_input_down(Input::I_DERECHA)) 
		{
			++x_mapa;
			automapa.refrescar_vista(x_mapa, y_mapa);
		}
		else if(input.es_input_down(Input::I_ARRIBA)) 
		{
			--y_mapa;
			automapa.refrescar_vista(x_mapa, y_mapa);
		}
		else if(input.es_input_down(Input::I_ABAJO)) 
		{
			++y_mapa;
			automapa.refrescar_vista(x_mapa, y_mapa);
		}
	}
}

void Controlador_pausa::dibujar(DLibV::Pantalla& pantalla)
{
	pantalla.limpiar(0, 0, 0, 255);

	representador.generar_vista(pantalla, automapa.obtener_vista(200, 200, 7));
}
