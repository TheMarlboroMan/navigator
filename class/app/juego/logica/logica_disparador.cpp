#include "logica_disparador.h"

using namespace App_Juego_Logica;

Logica_disparador::Logica_disparador(const App_Juego::Jugador& j)
	:jugador(j)
{

}

/**
* @return bool : si se ha podido o no insertar el disparo.
* @param vector<shared_ptr<Proyectil_base>> v : vector en el que se inserta el disparo.
* @param Jugador j : el jugador que ejecuta el disparo.
*/

void Logica_disparador::insertar_disparo_jugador(std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base> >&v)
{
	//TODO: Usar factoría...
	using namespace App_Juego_ObjetoJuego;
	float x=jugador.acc_espaciable_x();
	float y=jugador.acc_espaciable_y();
	DLibH::Vector_2d vector(0.0f, 0.0f);
	if(jugador.es_encarando_direccion(App_Definiciones::direcciones::derecha))  vector.x=350.0f;
	else vector.x=-350.0f;
	std::shared_ptr<Proyectil_normal> pr(new Proyectil_normal(x, y, 8, 8, vector, 25.0f, App_Juego_ObjetoJuego::Proyectil_normal::colores::rojo));
	v.push_back(pr);
}
