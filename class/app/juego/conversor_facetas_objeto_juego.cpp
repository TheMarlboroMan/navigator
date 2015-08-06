#include "conversor_facetas_objeto_juego.h"
//#include "../visitantes/visitante_objeto_juego_facetas.h"

#include "objetos_juego/bonus_tiempo.h"
#include "objetos_juego/bonus_salud.h"
#include "objetos_juego/enemigo_basico.h"

using namespace App_Juego;
using namespace App_Visitantes;
using namespace App_Interfaces;
using namespace App_Graficos;

/*
* Para cada facetas tenemos que escribir su propio visitante. Hay un visitante
* de facetas por ahí pero no nos sirve porque el objeto sobre el que estamos
* trabajando es "Objeto_Juego_I" y no del tipo que se necesita devolver. 
* Podríamos hacer dynamic_cast para ahorrar código, pero no me gusta.
*/

void Conversor_facetas_objeto_juego::extraer_representables(const std::vector<std::shared_ptr<Objeto_juego_I> > v, std::vector<const Representable *>& resultado)
{
	class V:public Visitante_objeto_juego
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

/*	
* Tristemente esto no funciona sin dynamic_cast. Y no me gustaría usarlo.

	Visitante_objeto_juego_facetas vis;
	for(auto& o : v) 
	{	
		o->recibir_visitante(vis);
		if(vis.facetas & objeto_juego_facetas::representable) resultado.push_back(&o); 
		vis.reset();
	}
*/

/*
* Aún más triste que esto no funciona porque los tipos no son siempre 
* compatibles según la declaración del template.

	VisTemplate<const Representable> vis(resultado);
	for(auto& o : v) o->recibir_visitante(vis);
*/
}

void Conversor_facetas_objeto_juego::extraer_borrables(const std::vector<std::shared_ptr<Objeto_juego_I> > v, std::vector<Borrable_I *>& resultado)
{
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
}

void Conversor_facetas_objeto_juego::extraer_bonus(const std::vector<std::shared_ptr<Objeto_juego_I> > v, std::vector<Bonus_I *>& resultado)
{
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
}
