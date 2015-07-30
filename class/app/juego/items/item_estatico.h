#ifndef ITEM_ESTATICO_H
#define ITEM_ESTATICO_H

#include "item_base.h"
#include "../actor.h"

/**
* Se define como un item que también es actor. 
**/

namespace App_Juego_Items
{
class Item_estatico:public App_Juego::Actor, public Item_base
{
	private:

	/////////////////////
	// Implementación de Item_base
	public:

	/////////////////////
	//Interface pública
	public:

	Item_estatico(float x, float y, unsigned int w, unsigned int h)
		:App_Juego::Actor(x, y, w, h), Item_base()
	{}

	Item_estatico()
		:App_Juego::Actor(), Item_base()
	{}
};
}

#endif
