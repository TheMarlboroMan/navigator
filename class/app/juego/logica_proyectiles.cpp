#include "logica_proyectiles.h"

using namespace App_Juego;

Logica_proyectiles::Logica_proyectiles()
{

}

/**
* @return bool : si se ha podido o no insertar el disparo.
* @param vector<shared_ptr<Proyectil_base>> v : vector en el que se inserta el disparo.
* @param Jugador j : el jugador que ejecuta el disparo.
*/

bool Logica_proyectiles::insertar_disparo_jugador(std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base> >&v, Jugador& j)
{
	//TODO: Evaluar si puede ejecutar el disparo.

	bool resultado=true;

	using namespace App_Juego_ObjetoJuego;
	float x=j.acc_espaciable_x();
	float y=j.acc_espaciable_y();
	std::shared_ptr<Proyectil_normal> pr(new Proyectil_normal(Proyectil_normal::Propiedades_proyectil_jugador(x, y)));

	//Establecer el vector según la dirección del jugador.
	DLibH::Vector_2d vector(0.0f, 0.0f);
	if(j.es_encarando_direccion(App_Definiciones::direcciones::derecha))  vector.x=200.0f;
	else vector.x=-200.0f;

	pr->establecer_vector(vector);
	v.push_back(pr);

	return resultado;
}


