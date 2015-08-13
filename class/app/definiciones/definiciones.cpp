#include "definiciones.h"

using namespace App_Definiciones;

App_Definiciones::direcciones App_Definiciones::obtener_direccion_contraria(App_Definiciones::direcciones s)
{
	switch(s)
	{
		case App_Definiciones::direcciones::arriba: return App_Definiciones::direcciones::abajo; break;
		case App_Definiciones::direcciones::abajo: return App_Definiciones::direcciones::arriba; break;
		case App_Definiciones::direcciones::derecha: return App_Definiciones::direcciones::izquierda; break;
		case App_Definiciones::direcciones::izquierda: return App_Definiciones::direcciones::derecha; break;
		default: return App_Definiciones::direcciones::nada; break;
	}
}

App_Definiciones::direcciones App_Definiciones::operator|(App_Definiciones::direcciones a, App_Definiciones::direcciones b)
{
	return static_cast<App_Definiciones::direcciones>(static_cast<int>(a) | static_cast<int>(b));
}

App_Definiciones::direcciones App_Definiciones::operator&(App_Definiciones::direcciones a, App_Definiciones::direcciones b)
{
	return static_cast<App_Definiciones::direcciones>(static_cast<int>(a) & static_cast<int>(b));
}


App_Definiciones::direcciones App_Definiciones::convertir_en_direccion(int v)
{
	switch(v)
	{
		case 1: return direcciones::arriba; break;
		case 2: return direcciones::derecha; break;
		case 4: return direcciones::abajo; break;
		case 8: return direcciones::izquierda; break;
		default: return direcciones::nada; break;
	}
}
