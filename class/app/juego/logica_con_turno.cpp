#include "logica_con_turno.h"

using namespace App_Juego;

Logica_con_turno::Logica_con_turno(const Jugador& j, const App_Niveles::Sala& s, float d)
	:jugador(j), sala(s), delta(d)
{

}

void Logica_con_turno::procesar(vector_oj v)
{
	for(auto& o : v)
	{
		if(es_con_turno(*o) && !o->es_borrar()) 
		{
			auto &f=o->como_facetador();
			f.con_turno->turno(delta);
			f.con_turno->recibir_visitante(*this);
		}
	}
}


void Logica_con_turno::visitar(App_Juego_ObjetoJuego::Enemigo_basico& o)
{
	//Encarar al jugador.
	auto vd=o.obtener_vector_para(jugador);
	auto direccion=App_Definiciones::direcciones::derecha;
	if(vd.x < 0.0) direccion=App_Definiciones::direcciones::izquierda;

	o.mut_direccion(direccion);

	//Moverse...
	auto v=o.acc_vector();
	o.desplazar_caja(v.x * delta, v.y * delta);

	//En caso de colisión o salir fuera del mundo, revertir.
	App_Colisiones::Calculador_colisiones cc;

	auto caja=o.copia_caja();
	if(cc.es_fuera_de_sala(caja, sala) || cc.celdas_en_caja(caja, sala).size())
	{
		v.x=-v.x;
		v.y=-v.y;
		o.establecer_vector(v);	
	}
}

void Logica_con_turno::visitar(App_Juego_ObjetoJuego::Proyectil_normal& o)
{
	auto v=o.acc_vector();
	o.desplazar_caja(v.x * delta, v.y * delta); 
}
