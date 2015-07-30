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

namespace App_Juego_Automapa
{

struct Definiciones_automapa
{
	private:
	Definiciones_automapa();

	public:
	static const int ANCHO=5;
	static const int ALTO=5;
	static const int MARGEN_ANCHO=2;
	static const int MARGEN_ALTO=2;
};

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
};

class Automapa
{
	/////////////
	//Propiedades
	private:
	std::vector<Unidad_automapa> unidades;
	std::vector<Unidad_automapa> vista;

	/////////////
	//Métodos privados...

	Unidad_automapa& localizar(int x, int y);

	/////////////
	//Interface pública
	public:

	/**
	* @param int pw
	* @param int ph
	* Prerellena el vector con casillas vacías, simplemente
	* para que estén ahí, en función del ancho y alto. Luego lo ordena.
	* Mete más casillas del ancho real del mapa con la finalidad de acomodar
	* espacios en blanco.
	*/

	void inicializar(int pw, int ph);

	/**
	* @param int px
	* @param int py
	* Marca como descubierta la casilla en la posición dada. A partir de
	* ese momento la casilla es ya visible.
	*/

	void descubrir(int px, int py);

	/**
	* @param int px
	* @param int py
	* @param App_Definiciones::direcciones pt
	* Especifica el tipo de la celda indicada.
	*/

	void configurar(int px, int py, App_Definiciones::direcciones pt);

	/**
	* @param int px	
	* @param int py
	* Genera un vector que representa la vista de ANCHO * ALTO casillas 
	* centradas en px, py. El vector se almacena en la clase como "vista".
	*/

	void refrescar_vista(int px, int py);

	const std::vector<Unidad_automapa>& acc_vista() const {return vista;} 
};
}
#endif
