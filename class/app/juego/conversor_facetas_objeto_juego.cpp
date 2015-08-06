#include "conversor_facetas_objeto_juego.h"
#include "../visitantes/visitante_objeto_juego_facetas.h"

#include "objetos_juego/bonus_tiempo.h"
#include "objetos_juego/bonus_salud.h"
#include "objetos_juego/enemigo_basico.h"

using namespace App_Juego;
using namespace App_Visitantes;
using namespace App_Interfaces;
using namespace App_Graficos;

/*
* Para cada facetas tenemos que escribir su propio visitante. 
* Nos vamos de hardcore y usamos dynamic cast basándonos en las facetas. Si
* las facetas se van de sincronía tenemos un problemón!.
*/


//TODO: Una posibilidad es que "Objeto_juego" sea la base de todas esas interfaces.
//El camino del cast sería hacia arriba, y no sería dynamic sino static.
//TODO: Ojo entonces con el problema del diamante!!!

void Conversor_facetas_objeto_juego::extraer_representables(const std::vector<std::shared_ptr<Objeto_juego_I> > v, std::vector<const Representable *>& resultado)
{
/*	class V:public Visitante_objeto_juego
	{
		private:
		typedef std::vector<const Representable *> t_res;
		t_res& v;

		public:
		V(t_res& r):v(r) {}
		virtual void visitar(App_Juego_ObjetoJuego::Bonus_tiempo& b) {v.push_back(&b);}
		virtual void visitar(App_Juego_ObjetoJuego::Bonus_salud& b) {v.push_back(&b);}
		virtual void visitar(App_Juego_ObjetoJuego::Enemigo_basico& b) {v.push_back(&b);}
	}vis(resultado);

	for(auto& o : v) o->recibir_visitante(vis);
*/

/*
* Aún más triste que esto no funciona porque los tipos no son siempre 
* compatibles según la declaración del template.

	VisTemplate<const Representable> vis(resultado);
	for(auto& o : v) o->recibir_visitante(vis);
*/

	Visitante_objeto_juego_facetas vis;
	for(auto& o : v) 
	{	
		o->recibir_visitante(vis);
		if( (vis.facetas & objeto_juego_facetas::representable) != objeto_juego_facetas::nada) resultado.push_back(dynamic_cast<const Representable *>(o.get()) ); 
		vis.reset();
	}
}

void Conversor_facetas_objeto_juego::extraer_borrables(const std::vector<std::shared_ptr<Objeto_juego_I> > v, std::vector<Borrable_I *>& resultado)
{
/*
	class V:public Visitante_objeto_juego
	{
		private:
		typedef std::vector<Borrable_I *> t_res;
		t_res& v;

		public:
		V(t_res& r):v(r) {}
		virtual void visitar(App_Juego_ObjetoJuego::Bonus_tiempo& b) {v.push_back(&b);}
		virtual void visitar(App_Juego_ObjetoJuego::Bonus_salud& b) {v.push_back(&b);}
		virtual void visitar(App_Juego_ObjetoJuego::Enemigo_basico& b) {v.push_back(&b);}
	}vis(resultado);

	for(auto& o : v) o->recibir_visitante(vis);
*/

	Visitante_objeto_juego_facetas vis;
	for(auto& o : v) 
	{	
		o->recibir_visitante(vis);
		if( (vis.facetas & objeto_juego_facetas::borrable) != objeto_juego_facetas::nada) resultado.push_back(dynamic_cast<Borrable_I *>(o.get()) ); 
		vis.reset();
	}
}

void Conversor_facetas_objeto_juego::extraer_bonus(const std::vector<std::shared_ptr<Objeto_juego_I> > v, std::vector<Bonus_I *>& resultado)
{
/*
	class V:public Visitante_objeto_juego
	{
		private:
		typedef std::vector<Bonus_I *> t_res;
		t_res& v;

		public:
		V(t_res& r):v(r) {}
		virtual void visitar(App_Juego_ObjetoJuego::Bonus_tiempo& b) {v.push_back(&b);}
		virtual void visitar(App_Juego_ObjetoJuego::Bonus_salud& b) {v.push_back(&b);}
		virtual void visitar(App_Juego_ObjetoJuego::Enemigo_basico& b) {}
	}vis(resultado);

	for(auto& o : v) o->recibir_visitante(vis);
*/

	Visitante_objeto_juego_facetas vis;
	for(auto& o : v) 
	{	
		o->recibir_visitante(vis);
		if( (vis.facetas & objeto_juego_facetas::bonus) != objeto_juego_facetas::nada) resultado.push_back(dynamic_cast<Bonus_I *>(o.get()) ); 
		vis.reset();
	}
}

void Conversor_facetas_objeto_juego::extraer_con_turno(const std::vector<std::shared_ptr<Objeto_juego_I> > v, std::vector<Con_turno_I *>& resultado)
{
/*
	class V:public Visitante_objeto_juego
	{
		private:
		typedef std::vector<Con_turno_I *> t_res;
		t_res& v;

		public:
		V(t_res& r):v(r) {}
		virtual void visitar(App_Juego_ObjetoJuego::Bonus_tiempo& b) {}
		virtual void visitar(App_Juego_ObjetoJuego::Bonus_salud& b) {}
		virtual void visitar(App_Juego_ObjetoJuego::Enemigo_basico& b) {v.push_back(&b);}
	}vis(resultado);

	for(auto& o : v) o->recibir_visitante(vis);
*/
	Visitante_objeto_juego_facetas vis;
	for(auto& o : v) 
	{	
		o->recibir_visitante(vis);
		if( (vis.facetas & objeto_juego_facetas::con_turno) != objeto_juego_facetas::nada) resultado.push_back(dynamic_cast<Con_turno_I *>(o.get()) ); 
		vis.reset();
	}
}
