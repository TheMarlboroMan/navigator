#include "logica_bonus.h"

using namespace App_Juego;

Logica_bonus::Logica_bonus(App_Interfaces::Recoge_bonus_I& rb)
	:recoge_bonus(rb)
{
	
}

void Logica_bonus::procesar(std::vector<std::shared_ptr<App_Interfaces::Bonus_I>>& v)
{
	const auto& e=recoge_bonus.obtener_espaciable_recogedor_bonus();

	for(auto& o : v)
	{		
		//Se comprueba la colisión antes de nada.
		if(o->es_bonus_para(e))
			o->recoger(recoge_bonus);
	}
}
