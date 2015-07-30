#include "definiciones.h"

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

