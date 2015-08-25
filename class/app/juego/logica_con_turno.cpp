#include "logica_con_turno.h"

using namespace App_Juego;

Logica_con_turno::Logica_con_turno(const Jugador& j, const App_Niveles::Sala& s, float d, std::vector<std::shared_ptr<App_Interfaces::Con_turno_I>>& p)
	:jugador(j), sala(s), delta(d), particulas(p)
{

}

void Logica_con_turno::procesar(std::vector<std::shared_ptr<App_Interfaces::Con_turno_I>>& v)
{
	auto f=[this](std::vector<std::shared_ptr<App_Interfaces::Con_turno_I>>& v)
	{
		for(auto& o : v)
		{
			if(!o->es_borrar()) 
			{
				o->turno(delta);
				o->recibir_visitante(*this);
			}
		}
	};
	f(v);
	f(particulas);

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

void Logica_con_turno::visitar(App_Juego_ObjetoJuego::Enemigo_rebote& o)
{
	//Moverse...
	auto v=o.acc_vector();
	o.desplazar_caja(v.x * delta, v.y * delta);

	//En caso de colisión o salir fuera del mundo, revertir.
	App_Colisiones::Calculador_colisiones cc;

	auto caja=o.copia_caja();
	auto cel=cc.celdas_en_caja(caja, sala);
	if(cc.es_fuera_de_sala(caja, sala) || cel.size())
	{
		if(cel.size())
		{
			if(v.x)
			{
				o.ajustar(*cel[0], v.x < 0 ? Actor_movil::posiciones_ajuste::izquierda : Actor_movil::posiciones_ajuste::derecha);
			}
			else if(v.y)
			{
				o.ajustar(*cel[0], v.y < 0 ? Actor_movil::posiciones_ajuste::arriba : Actor_movil::posiciones_ajuste::abajo);
			}			
		}

		o.cambiar_direccion();
	}
}

void Logica_con_turno::visitar(App_Juego_ObjetoJuego::Proyectil_normal& o)
{
	auto v=o.acc_vector();
	o.desplazar_caja(v.x * delta, v.y * delta); 
}

void Logica_con_turno::visitar(App_Juego_ObjetoJuego::Particula_fantasma& o)
{
	//TODO...
}

void Logica_con_turno::visitar(App_Juego_ObjetoJuego::Particula_explosion& o)
{
	//TODO...
}
