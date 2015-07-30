#ifndef ITEM_TIEMPO_H
#define ITEM_TIEMPO_H

#include "item_estatico.h"

namespace App_Juego_Items
{
class Item_tiempo:public Item_estatico
{
	///////////////////
	// Definiciones
	private:
	static const float TIEMPO_BASE;

	///////////////////
	// Propiedades...
	private:
	float tiempo;

	///////////////////
	// Implementación de item base.
	//TODO TODO: Hasta los cojones de visitantes.. Sistemas de mensajes mejor.
	//Llega un momento en que hay demasiadas jerarquías para cosas que podrían
	//hacerse por composición.
	virtual void recibir_visitante(Visitante_item_const& v) {v.visitar(*this);}
	virtual void recibir_visitante(Visitante_item& v)	{v.visitar(*this);}

	///////////////
	//Interface pública.
	public:

	Item_tiempo()
		:Item_estatico(), tiempo(TIEMPO_BASE)
	{}

	Item_tiempo(float x, float y, unsigned int w, unsigned int h)
		:Item_estatico(x, y, w, h), tiempo(TIEMPO_BASE)
	{}

	float acc_tiempo() const {return tiempo;}
	void mut_tiempo(float v) {tiempo=v;}
};
}

#endif
