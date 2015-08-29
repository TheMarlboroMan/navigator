#include "logica_generador_objetos_juego.h"

using namespace App_Juego;

Logica_generador_objetos_juego::Logica_generador_objetos_juego()
{
	factoria.establecer_contenedor(contenedor);
}


void Logica_generador_objetos_juego::procesar(std::vector<std::shared_ptr<App_Interfaces::Generador_objetos_juego_I>> v)
{
	//TODO: La factoría tendrá que ser un objeto un poco más complejo que una
	//factoría en si, puesto que se tendrá que pasar a cosas que van a disparar
	//y que necesitan, por ejemplo, saber la posición del jugador.
	//Quitaremos la interface de la factoría y por composición haremos una
	//nueva clase que implemente la factoria_i y contenga una factoría.
	//Esa clase además puede tener una referencia al jugador, por ejemplo.
	for(auto& o : v) o->generar_objetos(factoria);
}
