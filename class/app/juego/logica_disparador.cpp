#include "logica_disparador.h"

using namespace App_Juego;

Logica_disparador::Logica_disparador(std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base> >&v, const Jugador& j)
	:proyectiles_enemigos(v),
	jugador(j)
{

}

/**
* @return bool : si se ha podido o no insertar el disparo.
* @param vector<shared_ptr<Proyectil_base>> v : vector en el que se inserta el disparo.
* @param Jugador j : el jugador que ejecuta el disparo.
*/

bool Logica_disparador::insertar_disparo_jugador(std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base> >&v)
{
	//TODO: Evaluar si puede ejecutar el disparo.

	bool resultado=true;

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

	return resultado;
}

void Logica_disparador::procesar(std::vector<std::shared_ptr<App_Interfaces::Disparador_I>>& v)
{
	for(auto& o : v)
	{
		if(o->es_disparar())
		{
			o->recibir_visitante(*this);
		}
	}
}

void Logica_disparador::visitar(App_Juego_ObjetoJuego::Enemigo_basico& e)
{
	using namespace App_Juego_ObjetoJuego;
	using namespace DLibH;

	float x=e.acc_espaciable_x();
	float y=e.acc_espaciable_y();


	std::shared_ptr<Proyectil_normal> pr(new Proyectil_normal(Proyectil_normal::Propiedades_proyectil_jugador(x, y)));

	pr->establecer_vector(e.obtener_vector_para(jugador) * 200.0f);
	pr->mut_potencia(25.0f);
	pr->mut_color(Proyectil_normal::colores::azul);
	proyectiles_enemigos.push_back(pr);

	e.mut_disparar(false);
}
