#include "logica_generador_objetos_juego.h"

using namespace App_Juego_Logica;

Interface_creador_objetos::Interface_creador_objetos(App_Juego_Contenedores::Contenedor_objetos& co, App_Juego_Contenedores::Contenedor_volatiles& cv, App_Interfaces::Espaciable& es, const App_Lectores::Info_obstaculos_genericos& iog)
	:factoria(iog), contenedor_volatiles(cv), espaciable(es)
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

void Interface_creador_objetos::fabricar_trazador_humo(float x, float y, float tv, const DLibH::Vector_2d& v)
{
	auto ob=factoria_volatiles.crear_trazador_humo(x, y, tv, v);
	contenedor_volatiles.trazadores.push_back(ob);
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

void Interface_creador_objetos::fabricar_fantasma_jugador(float x, float y, float tv, float ve, App_Definiciones::direcciones direccion)
{
	auto ob=factoria_volatiles.crear_fantasma_jugador(x, y, tv, ve, direccion);
	contenedor_volatiles.particulas.push_back(ob);
}

void Interface_creador_objetos::fabricar_fantasma_bonus_tiempo(float x, float y, float tv, float ve)
{
	auto ob=factoria_volatiles.crear_fantasma_bonus_tiempo(x, y, tv, ve);
	contenedor_volatiles.particulas.push_back(ob);
}

void Interface_creador_objetos::fabricar_fantasma_bonus_salud(float x, float y, float tv, float ve)
{
	auto ob=factoria_volatiles.crear_fantasma_bonus_salud(x, y, tv, ve);
	contenedor_volatiles.particulas.push_back(ob);
}

void Interface_creador_objetos::fabricar_humo(float x, float y, float tv)
{
	auto ob=factoria_volatiles.crear_humo(x, y, tv);
	contenedor_volatiles.particulas.push_back(ob);
}

void Interface_creador_objetos::fabricar_particula_numero(float x, float y, size_t val)
{
	auto ob=factoria_volatiles.crear_particula_numero(x, y, val);
	contenedor_volatiles.particulas.push_back(ob);
}

void Interface_creador_objetos::fabricar_proyectil_normal_enemigo(float x, float y, int w, int h, const DLibH::Vector_2d& v, float pot)
{
	auto ob=factoria_volatiles.crear_proyectil_normal(x, y, w, h, v, pot);
	contenedor_volatiles.proyectiles_enemigos.push_back(ob);
}

void Interface_creador_objetos::fabricar_proyectil_rayo_estatico_enemigo(float x, float y, int w, int h, float pot)
{
	auto ob=factoria_volatiles.crear_proyectil_rayo_estatico(x, y, w, h, pot);
	contenedor_volatiles.proyectiles_enemigos.push_back(ob);
}

///////////////////////////////////

Logica_generador_objetos_juego::Logica_generador_objetos_juego(App_Juego::Jugador& j, const App_Lectores::Info_obstaculos_genericos& iog)
	:jugador(j), interface_crear(contenedor, contenedor_volatiles, j, iog)
{

}

void Logica_generador_objetos_juego::procesar(std::vector<App_Interfaces::Generador_objetos_juego_I *> v)
{
	for(auto& o : v) o->generar_objetos(interface_crear);
	jugador.generar_objetos(interface_crear);
}
