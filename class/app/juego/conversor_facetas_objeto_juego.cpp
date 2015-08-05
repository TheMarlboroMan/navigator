#include "conversor_facetas_objeto_juego.h"
#include "../visitantes/visitante_objeto_juego.h"

#include "objetos_juego/bonus_tiempo.h"
#include "objetos_juego/bonus_salud.h"
#include "objetos_juego/enemigo_basico.h"

using namespace App_Juego;
using namespace App_Visitantes;
using namespace App_Interfaces;
using namespace App_Graficos;

//TODO: Un único visitante brutal que saque las facetas haría todos estos
//métodos mucho más cortos. Simplemente procesaríamos las facetas y punto.


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

	for(auto& o : v) o->recibir_visitante(vis);
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
