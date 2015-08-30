#include "logica_con_turno.h"

using namespace App_Juego;

Logica_con_turno::Logica_con_turno(const Jugador& j, const App_Niveles::Sala& s, float d)
	:jugador(j), sala(s), delta(d)
{

}

void Logica_con_turno::procesar(std::vector<App_Interfaces::Con_turno_I *>& v)
{
	for(auto& o : v)
	{
		if(!o->es_borrar()) 
		{
			o->turno(delta);
			o->recibir_visitante(*this);
		}
	}
}

void Logica_con_turno::visitar(App_Juego_ObjetoJuego::Enemigo_basico& o)
{
	//TODO: This sucks: mover al propio enemigo básico, que venga cargado con lo que sea.
/**

* La interface debería tener:
	- Un blanco para encararlo.
	- Un método para saber si esta fuera de la sala.
	- Un método para obtener un puñado de espaciables con los que esté en colisión (dependencia de espaciables, realmente
		no sería necesario pero casi todo esto son espaciables).

	Los beneficios:

		- Eliminamos un visitante más :D!.
		- Todo el código de una clase está contenida en la misma.
		- Quitamos todo el código pestoso de cosas con turno que no hacen nada aquí.
	
	Los maleficios:

		- El modelo es más gordo.

Por tanto podría ser algo como:

class Contexto_turno_I
{
	/////////////////////////
	//Interface pública.

	public:

	virtual						~Contexto_turno();
	virtual float					acc_delta() const=0;
	virtual const Espaciable&			acc_blanco() const=0;
	virtual bool					es_fuera_sala(const Espaciable&e) const=0;
	virtual std::vector<const Espaciable *>		celdas_en_caja(const Espaciable&e) const=0;

}

la implementación concreta...

class Contexto_turno_juego:
	public Contexto_turno_I
{
	public:
						Contexto_turno_juego(float, const Sala& sala, Espaciable& jugador);

	virtual float				acc_delta() const {return delta;}
	virtual const Espaciable&		acc_blanco() const {return jugador;}
	virtual bool				es_fuera_sala(const Espaciable& e)
	{
		App_Colisiones::Calculador_colisiones cc;
		return cc.es_fuera_de_sala(e.copia_caja(), sala);
	}

	virtual std::vector<const Espaciable *>	celdas_en_caja(const Espaciable&e) const
	{
		App_Colisiones::Calculador_colisiones cc;
		return cc.celdas_en_caja(e.copia_caja(), sala);
	}

	private:

	float					delta;
	const Sala&				sala;
	const Espaciable&			jugador;
};

Esto lo instanciaríamos en el controlador y ya estaríamos listos. Según crecieran
las necesidades podríamos mejorar el contexto.

Y la conversión de este trozo de código a ese uso...

void turno(Contexto_turno_I& ct)
{
	float delta=ct.acc_delta();

	//Encarar al jugador.
	auto vd=o.obtener_vector_para(ct.acc_blanco());

	mut_direccion(vd.x < 0.0 ? App_Definiciones::direcciones::izquierda : App_Definiciones::direcciones::derecha);

	//Moverse...
	auto v=o.acc_vector();
	desplazar_caja(v.x * delta, v.y * delta);

	//En caso de colisión o salir fuera del mundo, revertir.
	App_Colisiones::Calculador_colisiones cc;

	auto caja=copia_caja();
	if(ct.es_fuera_sala(caja) || ct.celdas_en_caja(caja))
	{
		v.x=-v.x;
		v.y=-v.y;
		establecer_vector(v);
	}
}
*/


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
	//TODO: Again, this sucks.

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

//TODO: Vienen todos vacíos: esto esta mál pensado de coj.

void Logica_con_turno::visitar(App_Juego_ObjetoJuego::Proyectil_normal& o)
{
	//Nada...
}

void Logica_con_turno::visitar(App_Juego_ObjetoJuego::Particula_fantasma& o)
{
	//Nada...
}

void Logica_con_turno::visitar(App_Juego_ObjetoJuego::Particula_explosion& o)
{
	//Nada...
}

void Logica_con_turno::visitar(App_Juego_ObjetoJuego::Particula_chatarra& o)
{
	//Nada...
}

void Logica_con_turno::visitar(App_Juego_ObjetoJuego::Particula_chispa& o)
{
	//Nada...
}
