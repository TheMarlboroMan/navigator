#include "logica_generador_objetos_juego.h"

using namespace App_Juego;

void Interface_creador_objetos::establecer_contenedor(App_Juego_Contenedores::Contenedor_objetos& c)
{
	factoria.establecer_contenedor(c);
}

void Interface_creador_objetos::establecer_contenedor_volatiles(App_Juego_Contenedores::Contenedor_volatiles& c)
{
	factoria.establecer_contenedor_volatiles(c);
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
	auto ob=factoria.crear_chispa(x, y, tv, v);
	factoria.insertar(ob);
}

void Interface_creador_objetos::fabricar_explosion(float x, float y, float tv, const DLibH::Vector_2d& v)
{
	auto ob=factoria.crear_explosion(x, y, tv, v);
	factoria.insertar(ob);
}

void Interface_creador_objetos::fabricar_chatarra(float x, float y, float tv, const DLibH::Vector_2d& v)
{
	auto ob=factoria.crear_chatarra(x, y, tv, v);
	factoria.insertar(ob);
}


void Interface_creador_objetos::fabricar_fantasma(float x, float y, float tv, float ve, App_Definiciones::direcciones direccion, int recurso, const DLibH::Caja<int, int>& recorte)
{
	auto ob=factoria.crear_fantasma(x, y, tv, ve, direccion, recurso, recorte);
	factoria.insertar(ob);
}
///////////////////////////////////

Logica_generador_objetos_juego::Logica_generador_objetos_juego(std::vector<std::shared_ptr<App_Interfaces::Generador_objetos_juego_I>>& g, App_Interfaces::Generador_objetos_juego_I& j)
	:generadores(g), jugador(j)
{
	interface_crear.establecer_contenedor(contenedor);
	interface_crear.establecer_contenedor_volatiles(contenedor_volatiles);
}

void Logica_generador_objetos_juego::procesar(std::vector<std::shared_ptr<App_Interfaces::Generador_objetos_juego_I>> v)
{
	for(auto& o : v) o->generar_objetos(interface_crear);
	for(auto& o : generadores) o->generar_objetos(interface_crear);
	jugador.generar_objetos(interface_crear);
}
