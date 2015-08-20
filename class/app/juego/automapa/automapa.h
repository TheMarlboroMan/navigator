#ifndef AUTOMAPA_H
#define AUTOMAPA_H

/**
* El automapa guarda la estructura completa del mapa en Unidad_automapa, que
* es cada una de las salas. Cualquier casilla, tenga o no tenga algo, guarda
* su tipo y su posición.
* Usando el automapa se pueden marcar las salas visitadas. Con cada visita se
* puede refrescar la vista del automapa para cambiar el centro y mostrar las
* nuevas casillas.
* Al solicitar una vista del automapa se devuelve un vector de UnidadAutomapa
* que representa una rejilla de ANCHO*ALTO.
*/

#include <vector>
#include <algorithm>
#include "../../definiciones/definiciones.h"

//TODO: Actualizar makefile.
#include "../../interfaces/representable_i.h"
#include "../../graficos/bloque_transformacion_representable.h"
#include "../../recursos.h"
#include "../../definiciones/definiciones.h"

namespace App_Juego_Automapa
{
struct Unidad_automapa
{
	int x, y;
	App_Definiciones::direcciones tipo;
	bool visitado;

	bool operator<(const Unidad_automapa& u) const
	{
		if(y < u.y) return true;
		else if(y > u.y) return false;
		else return x < u.x;
	}

	Unidad_automapa(int px, int py)
		:x(px), y(py), tipo(App_Definiciones::direcciones::nada), visitado(false)
	{}

	Unidad_automapa(const Unidad_automapa& o)
		:x(o.x), y(o.y), tipo(o.tipo), visitado(o.visitado)
	{}
};

struct Vista_unidad_automapa:
	public Unidad_automapa,
	public App_Interfaces::Representable_I
{
	static int pos_x_automapa;
	static int pos_y_automapa;
	static int dim_celda_automapa;
	mutable bool actual;

	Vista_unidad_automapa(const Unidad_automapa& u)
		:Unidad_automapa(u), actual(false)
	{}

	virtual unsigned short int 		obtener_profundidad_ordenacion() const {return 0;}
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b) const;
	virtual bool				es_representable_borrar() const {return false;}
};

class Automapa
{
	/////////////
	//Interface pública
	public:

						Automapa(int w, int h);
	void 					inicializar(int pw, int ph);
	void 					descubrir(int px, int py);
	void					configurar(int px, int py, App_Definiciones::direcciones pt);
	void 					refrescar_vista(int px, int py);
	void 					refrescar_vista();
	void					establecer_posicion_actual(int px, int py);
	std::vector<const App_Interfaces::Representable_I *>	obtener_vista(int px, int py, int pdim) const;

	/////////////
	//Propiedades
	private:
	std::vector<Unidad_automapa> 		unidades;
	std::vector<Vista_unidad_automapa> 	vista;
	
	int					w_vista, h_vista;
	int					x_actual, y_actual;
	int					margen_w, margen_h;

	/////////////
	//Métodos privados...

	Unidad_automapa& 			localizar(int x, int y);

};
}
#endif
