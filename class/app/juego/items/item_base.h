#ifndef ITEM_BASE_H
#define ITEM_BASE_H

#include "visitante_item.h"

/*
* Una base para el visitante de items. En este punto aún no se ha definido como 
* un actor dinámico o estático.
*/

namespace App_Juego_Items
{

class Item_base
{
	////////////////////
	//Interfaz pública
	public:
	virtual void recibir_visitante(Visitante_item_const&)=0;
	virtual void recibir_visitante(Visitante_item&)=0;
};
}

#endif
