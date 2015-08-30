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
	using namespace App_Juego_ObjetoJuego;
	float x=jugador.acc_espaciable_x();
	float y=jugador.acc_espaciable_y();
	std::shared_ptr<Proyectil_normal> pr(new Proyectil_normal(Proyectil_normal::Propiedades_proyectil_jugador(x, y)));

	//Establecer el vector según la dirección del jugador.
	DLibH::Vector_2d vector(0.0f, 0.0f);
	if(jugador.es_encarando_direccion(App_Definiciones::direcciones::derecha))  vector.x=350.0f;
	else vector.x=-350.0f;

	pr->establecer_vector(vector);
	pr->mut_potencia(25.0f);
	v.push_back(pr);
}
