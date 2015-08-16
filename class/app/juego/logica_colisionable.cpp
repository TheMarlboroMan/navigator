#include "logica_colisionable.h"
#include "objetos_juego/enemigo_basico.h"

using namespace App_Juego;

Logica_colisionable::Logica_colisionable(Jugador& j)
	:jugador(j)
{

}

/**
* Cuando estamos llamando a cualquiera de estas fases hemos llegado al punto
* en que la colisión con el elemento está verificada y sólo tenemos que correr
* la lógica de turno.
*/

/**
* Dado que es muy complejo hacer un sistema de colisiones de cuerpos, 
* simplemente asumimos que el jugador recibe un buen impacto.
*/

void Logica_colisionable::visitar(App_Juego_ObjetoJuego::Enemigo_basico& b)
{
	jugador.recibir_impacto(2.5f);
}

void Logica_colisionable::visitar(App_Juego_ObjetoJuego::Salida& b)
{
	std::cout<<"SALIDA"<<std::endl;
}

/*
	using namespace App_Interfaces;

	//TODO: Si el jugador está estacionario no se detecta origen de colisión...

	//TODO: Otra opción es separar los ejes X e Y del enemigo_basico.

	//TODO: Otra opcíón es que puedan trasparasarse y punto.

	//TODO: Otra opción es que el jugador no se mueve, sino el enemigo básico.


	//TODO: Mover a un método aparte.

	//Controlar la posición anterior del jugador para moverlo a la nueva posición.
	auto cj=jugador.acc_posicion_anterior(); 

	auto pos=Actor_movil::posiciones_ajuste::nada;
	auto vec=Movil::t_vector::V_X;

	if(b.es_sobre(cj)) 			
	{
std::cout<<"POR ENCIMA"<<std::endl;
		pos=Actor_movil::posiciones_ajuste::arriba;
		vec=Movil::t_vector::V_Y;
	}
	else if(b.es_bajo(cj))			
	{
std::cout<<"POR BAJO"<<std::endl;
		pos=Actor_movil::posiciones_ajuste::abajo;
		vec=Movil::t_vector::V_Y;
	}
	else if(b.es_a_la_izquierda_de(cj))	
	{
std::cout<<"POR IZQ"<<std::endl;
		pos=Actor_movil::posiciones_ajuste::derecha;
	}
	else if(b.es_a_la_derecha_de(cj))	
	{
std::cout<<"POR DER"<<std::endl;
		pos=Actor_movil::posiciones_ajuste::arriba;
	}

	//TODO: ¿Qué ocurre cuando el ajuste es "NADA" por una colisión perfecta en diagonal?.

	//TODO: ¿Qué ocurre cuando se pone en una celda siendo empujado hacia abajo???.

	//TODO: ¿Qué pasa cuando en el turno anterior estaba justo en la diagonal?.

	if(pos!=Actor_movil::posiciones_ajuste::nada)
	{
		jugador.ajustar(b, pos); 
		jugador.establecer_vector(0.0f, vec);
		//TODO: Forzar posición anterior???.
	}

	//El jugador sufre un impacto.
*/

void Logica_colisionable::procesar(std::vector<std::shared_ptr<App_Interfaces::Colisionable_I>>& v)
{
	for(auto& o : v)
	{		
		if(o->es_colision_para(jugador))
		{
			o->recibir_visitante(*this);
		}
	}
}
