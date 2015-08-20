#include "automapa.h"
#include <stdexcept>

using namespace App_Juego_Automapa;

int Vista_unidad_automapa::pos_x_automapa=0;
int Vista_unidad_automapa::pos_y_automapa=0;
int Vista_unidad_automapa::dim_celda_automapa=0;

Automapa::Automapa(int pw, int ph)
	:w_vista(pw), h_vista(ph), 
	x_actual(0), y_actual(0),
	margen_w(w_vista/2), margen_h(h_vista/2)
{
	if(! (w_vista % 2) || !(h_vista % 2))
	{
		throw new std::runtime_error("El automapa debe inicializarse con valores impares");
	}
}

/**
* @param int pw : ancho del mapa
* @param int ph : alto del mapa
* Prerellena el vector con casillas vacías, simplemente
* para que estén ahí, en función del ancho y alto. Luego lo ordena.
* Mete más casillas del ancho real del mapa con la finalidad de acomodar
* espacios en blanco.
*/

void Automapa::inicializar(int pw, int ph)
{
	//Vaciar las unidades...
	unidades.clear();

	//Calcular los límites...
	int ini_x=-margen_w;
	int fin_x=pw+margen_w;

	int ini_y=-margen_h;
	int fin_y=ph+margen_h;

	for(int y=ini_y; y <= fin_y; ++y)
	{
		for(int x=ini_x; x <=fin_x; ++x)
		{
			unidades.push_back(Unidad_automapa(x, y));
		}
	}
}

/**
* @param int px
* @param int py
* Marca como descubierta la casilla en la posición dada. A partir de
* ese momento la casilla es ya visible.
*/


void Automapa::descubrir(int px, int py)
{
	localizar(px, py).visitado=true;
}

Unidad_automapa& Automapa::localizar(int x, int y)
{
	for(Unidad_automapa& u : unidades)
	{
		if(u.x==x && u.y==y) return u;
	}
	throw std::logic_error("No se localiza la unidad de automapa");
}

/**
* @param int px
* @param int py
* @param App_Definiciones::direcciones pt
* Especifica el tipo de la celda indicada.
*/

void Automapa::configurar(int px, int py, App_Definiciones::direcciones pt)
{
	localizar(px, py).tipo=pt;
}

/**
* @param int px	
* @param int py
* Genera un vector que representa la vista de ANCHO * ALTO casillas 
* centradas en px, py. El vector se almacena en la clase como "vista".
*/

void Automapa::refrescar_vista(int px, int py)
{
	vista.clear();

	//Calcular los límites...
	int ini_x=px-margen_w;
	int fin_x=ini_x + w_vista-1;

	int ini_y=py-margen_h;
	int fin_y=ini_y+h_vista-1;

	for(int y=ini_y; y <= fin_y; ++y)
	{
		for(int x=ini_x; x <=fin_x; ++x)
		{
			auto copia=localizar(x, y);
			vista.push_back(Vista_unidad_automapa(copia));			
		}
	}
}

void Automapa::refrescar_vista()
{
	refrescar_vista(x_actual, y_actual);
}


void Automapa::establecer_posicion_actual(int px, int py)
{
	x_actual=px;
	y_actual=py;
}
/*
void Automapa::dibujar(DLibV::Pantalla& pantalla)
{
//	int x=0, y=0;

//	for(const auto& u : vista)
//	{
//		bool es_actual=u.x==x_actual && u.y==y_actual;
//		representador.dibujar_pieza_automapa(pantalla, x, y, u.visitado ? u.tipo : App_Definiciones::direcciones::nada, es_actual);
//		if(++x==automapa.acc_w_vista())
//		{
//			x=0; ++y;
//		}
//	}
}
*/

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
		rep->establecer_posicion(pos_x_automapa + (x * dim_celda_automapa), 
			pos_y_automapa + (y * dim_celda_automapa), 
			dim_celda_automapa, dim_celda_automapa);

		return rep;
	};

	//En primer lugar, el fondo...
	auto fondo=preparar(x, y);
	//TODO TODO TODO...
	int xfondo=actual ? 16 * dim_celda_automapa : 0;
	fondo->establecer_recorte(xfondo, 0, dim_celda_automapa, dim_celda_automapa);
	b.insertar_en_grupo(fondo);

	//if(visitado)
	{
		//Y ahora el frente.
		auto frente=preparar(x, y);
		int pos=0;
		if( (tipo & direcciones::arriba) != direcciones::nada) pos+=1;
		if( (tipo & direcciones::derecha) != direcciones::nada) pos+=2;
		if( (tipo & direcciones::abajo) != direcciones::nada) pos+=4;
		if( (tipo & direcciones::izquierda) != direcciones::nada) pos+=8;
		frente->establecer_recorte(pos * dim_celda_automapa, 0, dim_celda_automapa, dim_celda_automapa);
		b.insertar_en_grupo(frente);
	}
}

std::vector<const App_Interfaces::Representable_I *> Automapa::obtener_vista(int px, int py, int pdim) const
{
	//TODO: A cada uno de ellos darle el desplazamiento necesario, of course.
	std::vector<const App_Interfaces::Representable_I *> res;
	auto &v=vista.front();
	v.pos_x_automapa=px;
	v.pos_y_automapa=py;
	v.dim_celda_automapa=pdim;

	for(auto& v : vista) 
	{
		v.actual=v.x==x_actual && v.y==y_actual;
		res.push_back(&v);
	}
	return res;
}
