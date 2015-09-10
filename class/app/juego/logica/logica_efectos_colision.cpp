#include "logica_efectos_colision.h"

using namespace App_Juego_Logica;

Logica_efectos_colision::Logica_efectos_colision(App_Juego_Sistemas::Contador_tiempo& t, App_Juego::Jugador& j)
	:espaciable(j), ecr(t, j)
{

}

void Logica_efectos_colision::procesar(std::vector<App_Interfaces::Efecto_colision_I *>& v)
{
	for(auto& ec : v) 
	{
		if(ec->es_colision_para(espaciable))
		{
			ec->efecto_colision(ecr);
		}
	}
}
