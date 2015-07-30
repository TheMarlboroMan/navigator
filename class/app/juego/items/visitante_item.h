#ifndef VISITANTE_ITEM_H
#define VISITANTE_ITEM_H

namespace App_Juego_Items
{

//Forward declarations.
class Item_base;
class Item_tiempo;

class Visitante_item_const
{
	public:
	virtual void visitar(const Item_base&);
	virtual void visitar(const Item_tiempo&);
};

class Visitante_item
{
	public:

	virtual void visitar(const Item_base&);
	virtual void visitar(const Item_tiempo&);
};

}

#endif
