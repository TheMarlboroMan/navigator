#include "representador.h"
#include "../recursos.h"

using namespace App_Graficos;
using namespace App_Interfaces;

Representador::Representador()
{

}

Representador::~Representador()
{

}

unsigned int Representador::generar_vista(
	DLibV::Pantalla& pantalla, 
	DLibV::Camara& camara, 
	const std::vector<const Representable_I *>& v)
{
	unsigned int total=0;

	for(const Representable_I * r : v)
	{
		r->transformar_bloque(bloque_transformacion);
		if(bloque_transformacion.rep->volcar(pantalla, camara)) ++total;
	}

	return total;
}

unsigned int Representador::generar_vista(
	DLibV::Pantalla& pantalla, 
	const std::vector<const Representable_I *>& v)
{
	unsigned int total=0;

	for(const Representable_I * r : v)
	{
		r->transformar_bloque(bloque_transformacion);
		if(bloque_transformacion.rep->volcar(pantalla)) ++total;
	}

	return total;
}

void Representador::dibujar_marco_automapa(DLibV::Pantalla&)
{
	//TODO...
}

void Representador::dibujar_pieza_automapa(DLibV::Pantalla& pantalla, int x, int y, App_Definiciones::direcciones t)
{
	using namespace App;
	using namespace App_Definiciones;
	DLibV::Representacion_bitmap_estatica rep_bmp;
	rep_bmp.establecer_alpha(255);
	rep_bmp.establecer_modo_blend(DLibV::Representacion::BLEND_ALPHA);
	rep_bmp.establecer_textura(DLibV::Gestor_texturas::obtener(Recursos_graficos::RT_AUTOMAPA));
	rep_bmp.establecer_posicion(X_AUTOMAPA + (x * DIM_AUTOMAPA), 
			Y_AUTOMAPA + (y * DIM_AUTOMAPA), 
			DIM_AUTOMAPA, DIM_AUTOMAPA);

	//El fondo...
	rep_bmp.establecer_recorte(0, 0, DIM_AUTOMAPA, DIM_AUTOMAPA);
	rep_bmp.volcar(pantalla);
	std::vector<direcciones> v {direcciones::arriba, direcciones::derecha, direcciones::abajo, direcciones::izquierda};


	for(direcciones val : v)
	{
		if( (t & val) != direcciones::nada)
		{
			
			switch(t & val)
			{
				case direcciones::arriba: rep_bmp.establecer_recorte(DIM_AUTOMAPA, 0, DIM_AUTOMAPA, DIM_AUTOMAPA); break;
				case direcciones::derecha: rep_bmp.establecer_recorte(2*DIM_AUTOMAPA, 0, DIM_AUTOMAPA, DIM_AUTOMAPA); break;
				case direcciones::abajo: rep_bmp.establecer_recorte(3*DIM_AUTOMAPA, 0, DIM_AUTOMAPA, DIM_AUTOMAPA); break;
				case direcciones::izquierda: rep_bmp.establecer_recorte(4*DIM_AUTOMAPA, 0, DIM_AUTOMAPA, DIM_AUTOMAPA); break;
				case direcciones::nada: break;
			}

			rep_bmp.volcar(pantalla);
		}
	}
}

