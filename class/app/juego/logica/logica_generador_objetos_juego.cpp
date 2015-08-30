#include "logica_generador_objetos_juego.h"

using namespace App_Juego_Logica;

Interface_creador_objetos::Interface_creador_objetos(App_Juego_Contenedores::Contenedor_objetos& co, App_Juego_Contenedores::Contenedor_volatiles& cv, App_Interfaces::Espaciable& es)
	:contenedor_volatiles(cv), espaciable(es)
{
	factoria.establecer_contenedor(co);
}

void Interface_creador_objetos::fabricar_bonus_tiempo(float x, float y, float t)
{
	auto ob=factoria.crear_bonus_tiempo(x, y, t);
	factoria.insertar(ob);
}

void Interface_creador_objetos::fabricar_bonus_salud(float x, float y, float t)
{
	auto ob=factoria.crear_bonus_salud(x, y, t);
	factoria.insertar(ob);
}

void Interface_creador_objetos::fabricar_chispa(float x, float y, float tv, const DLibH::Vector_2d& v)
{
	auto ob=factoria_volatiles.crear_chispa(x, y, tv, v);
	contenedor_volatiles.particulas.push_back(ob);
}

void Interface_creador_objetos::fabricar_explosion(float x, float y, float tv, const DLibH::Vector_2d& v)
{
	auto ob=factoria_volatiles.crear_explosion(x, y, tv, v);
	contenedor_volatiles.particulas.push_back(ob);
}

void Interface_creador_objetos::fabricar_chatarra(float x, float y, float tv, const DLibH::Vector_2d& v)
{
	auto ob=factoria_volatiles.crear_chatarra(x, y, tv, v);
	contenedor_volatiles.particulas.push_back(ob);
}


void Interface_creador_objetos::fabricar_fantasma(float x, float y, float tv, float ve, App_Definiciones::direcciones direccion, int recurso, const DLibH::Caja<int, int>& recorte)
{
	auto ob=factoria_volatiles.crear_fantasma(x, y, tv, ve, direccion, recurso, recorte);
	contenedor_volatiles.particulas.push_back(ob);
}

void Interface_creador_objetos::fabricar_proyectil_normal_enemigo(float x, float y, int w, int h, const DLibH::Vector_2d& v, float pot)
{
	auto ob=factoria_volatiles.crear_proyectil_normal(x, y, w, h, v, pot);
	contenedor_volatiles.proyectiles_enemigos.push_back(ob);
}

///////////////////////////////////

Logica_generador_objetos_juego::Logica_generador_objetos_juego(App_Juego::Jugador& j)
	:jugador(j), interface_crear(contenedor, contenedor_volatiles, j)
{

}

void Logica_generador_objetos_juego::procesar(std::vector<App_Interfaces::Generador_objetos_juego_I *> v)
{
	for(auto& o : v) o->generar_objetos(interface_crear);
	jugador.generar_objetos(interface_crear);
}
