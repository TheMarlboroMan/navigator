#ifndef PROTO_SALA_H
#define PROTO_SALA_H

#include "../definiciones/definiciones.h"

namespace App_Generador
{
class Proto_sala
{
	/////////////
	//Definiciones
	public:
	enum class tipos {inicio, fin, normal};

	/////////////
	//Propiedades
	private:

	int x, y;
	App_Definiciones::direcciones salidas;
	bool principal; //Puede ser principal o no principal. No se representa con flags.
	tipos tipo;

	///////////////
	//Interface pública
	public:

	int acc_x() const {return x;}
	int acc_y() const {return y;}
	App_Definiciones::direcciones acc_salidas() const {return salidas;}
	bool es_principal() const {return principal;}
	tipos acc_tipo() const {return tipo;}

	bool con_salida_en(App_Definiciones::direcciones pos) {return (salidas & pos) != App_Definiciones::direcciones::nada;}
	bool es_en_posicion(int px, int py) {return x==px && y==py;}

	void mut_salidas(App_Definiciones::direcciones pv) {salidas=pv;}
	void mut_principal(bool pv) {principal=pv;}
	void mut_tipo(tipos pv) {tipo=pv;}

	/**
	* @param int px
	* @param int py
	* Suma los valores de px y py a x e y. Se usará para poner la celda que
	* esté más arriba y a la izquierda en la posición 0,0.
	*/
	void normalizar(int px, int py)
	{
		x+=px;
		y+=py;
	}


	/**
	* @param int px
	* @param int py
	* @param int ps : indica las salidas según las flags t_salidas
	* @param bool pp : indica si es principal.
	* @param tipos pt : indica el tipo de la sala.
	*
	* Suma los valores de px y py a x e y. Se usará para poner la celda que
	* esté más arriba y a la izquierda en la posición 0,0.
	*/

	Proto_sala(int px, int py, App_Definiciones::direcciones ps=App_Definiciones::direcciones::nada, bool pp=true, tipos pt=tipos::normal)
		:x(px), y(py), salidas(ps), principal(pp),
		tipo(pt)
	{}
};
}

#endif
