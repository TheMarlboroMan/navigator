#include "factoria_objetos_volatiles.h"

using namespace App_Juego_Factorias;
using namespace App_Juego_ObjetoJuego;

std::shared_ptr<App_Juego_ObjetoJuego::Particula_chispa> Factoria_objetos_volatiles::crear_chispa(float x, float y, float tv, const DLibH::Vector_2d& v)
{
	auto res=std::shared_ptr<Particula_chispa>(new Particula_chispa(x, y, tv, v));
	return res;
}

std::shared_ptr<App_Juego_ObjetoJuego::Particula_explosion> Factoria_objetos_volatiles::crear_explosion(float x, float y, float tv, const DLibH::Vector_2d& v)
{
	auto res=std::shared_ptr<Particula_explosion>(new Particula_explosion(x, y, tv, v));
	return res;
}

std::shared_ptr<App_Juego_ObjetoJuego::Particula_chatarra> Factoria_objetos_volatiles::crear_chatarra(float x, float y, float tv, const DLibH::Vector_2d& v)
{
	auto res=std::shared_ptr<Particula_chatarra>(new Particula_chatarra(x, y, tv, v));
	return res;
}

std::shared_ptr<App_Juego_ObjetoJuego::Particula_fantasma_jugador> Factoria_objetos_volatiles::crear_fantasma_jugador(float x, float y, float tv, float ve, App_Definiciones::direcciones direccion)
{
	auto res=std::shared_ptr<Particula_fantasma_jugador>(new Particula_fantasma_jugador(x, y, tv, ve, direccion));
	return res;
}

std::shared_ptr<App_Juego_ObjetoJuego::Particula_fantasma_bonus_tiempo> Factoria_objetos_volatiles::crear_fantasma_bonus_tiempo(float x, float y, float tv, float ve)
{
	auto res=std::shared_ptr<Particula_fantasma_bonus_tiempo>(new Particula_fantasma_bonus_tiempo(x, y, tv, ve));
	return res;
}

std::shared_ptr<App_Juego_ObjetoJuego::Particula_fantasma_bonus_salud> Factoria_objetos_volatiles::crear_fantasma_bonus_salud(float x, float y, float tv, float ve)
{
	auto res=std::shared_ptr<Particula_fantasma_bonus_salud>(new Particula_fantasma_bonus_salud(x, y, tv, ve));
	return res;
}

std::shared_ptr<App_Juego_ObjetoJuego::Particula_numero> Factoria_objetos_volatiles::crear_particula_numero(float x, float y, size_t val, App_Definiciones::colores::colores_texto col)
{
	auto res=std::shared_ptr<Particula_numero>(new Particula_numero(x, y, 1.f, val, col, DLibH::Vector_2d(0.0f, -60.0f)));
	return res;
}

std::shared_ptr<App_Juego_ObjetoJuego::Particula_humo>	Factoria_objetos_volatiles::crear_humo(float x, float y, float tv)
{
	auto res=std::shared_ptr<Particula_humo>(new Particula_humo(x, y, tv));
	return res;
}

std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_normal> Factoria_objetos_volatiles::crear_proyectil_normal(float x, float y, int w, int h, const DLibH::Vector_2d& v, float pot)
{
	//TODO: Poner unas definiciones para el color fuera del proyectil.
	auto res=std::shared_ptr<Proyectil_normal>(new Proyectil_normal(x, y, w, h, v, pot, App_Juego_ObjetoJuego::Proyectil_normal::colores::azul));
	return res;
}

std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_rayo_estatico> Factoria_objetos_volatiles::crear_proyectil_rayo_estatico(float x, float y, int w, int h, float pot)
{
	auto res=std::shared_ptr<Proyectil_rayo_estatico>(new Proyectil_rayo_estatico(x, y, w, h, pot));
	return res;
}

std::shared_ptr<App_Juego_ObjetoJuego::Trazador_humo> Factoria_objetos_volatiles::crear_trazador_humo(float x, float y, float tv, const DLibH::Vector_2d& v)
{
	auto res=std::shared_ptr<Trazador_humo>(new Trazador_humo(x, y, tv, v));
	return res;
}
