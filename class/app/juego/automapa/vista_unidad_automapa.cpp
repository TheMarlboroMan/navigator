#include "vista_unidad_automapa.h"

using namespace App_Juego_Automapa;

int Vista_unidad_automapa::pos_x_automapa=0;
int Vista_unidad_automapa::pos_y_automapa=0;
int Vista_unidad_automapa::dim_celda_automapa=0;

void Vista_unidad_automapa::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const
{
	using namespace App;
	using namespace App_Definiciones;
	using namespace App_Graficos;

	b.establecer_tipo(Bloque_transformacion_representable::tipos::TR_GRUPO_ESTATICO);

	auto preparar=[this](int x, int y)
	{
		DLibV::Representacion_bitmap_estatica * rep=new DLibV::Representacion_bitmap_estatica;
		rep->establecer_alpha(255);
		rep->establecer_modo_blend(DLibV::Representacion::BLEND_ALPHA);
		rep->establecer_textura(DLibV::Gestor_texturas::obtener(Recursos_graficos::RT_AUTOMAPA));
		rep->establecer_posicion(pos_x_automapa + (vista_x * dim_celda_automapa), 
			pos_y_automapa + (vista_y * dim_celda_automapa), 
			dim_celda_automapa, dim_celda_automapa);

		return rep;
	};

	//En primer lugar, el fondo...
	auto fondo=preparar(x, y);
	int xfondo=actual ? 16 * dim_celda_automapa : 0;
	fondo->establecer_recorte(xfondo, 0, dim_celda_automapa, dim_celda_automapa);
	b.insertar_en_grupo(fondo);

	int pos=0;
	if( (tipo & direcciones::arriba) != direcciones::nada) pos+=1;
	if( (tipo & direcciones::derecha) != direcciones::nada) pos+=2;
	if( (tipo & direcciones::abajo) != direcciones::nada) pos+=4;
	if( (tipo & direcciones::izquierda) != direcciones::nada) pos+=8;

	if(visitado) // && pos)
	{
		//Y ahora el frente.
		auto frente=preparar(x, y);
		frente->establecer_recorte(pos * dim_celda_automapa, 0, dim_celda_automapa, dim_celda_automapa);
		b.insertar_en_grupo(frente);
	}
}
