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

std::shared_ptr<App_Juego_ObjetoJuego::Particula_fantasma> Factoria_objetos_volatiles::crear_fantasma(float x, float y, float tv, float ve, App_Definiciones::direcciones direccion, int recurso, const DLibH::Caja<int, int>& recorte)
{
	auto res=std::shared_ptr<Particula_fantasma>(new Particula_fantasma(x, y, tv, ve, direccion, recurso, recorte));
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

std::shared_ptr<App_Juego_ObjetoJuego::Trazador_humo> Factoria_objetos_volatiles::crear_trazador_humo(float x, float y, float tv, const DLibH::Vector_2d& v)
{
	auto res=std::shared_ptr<Trazador_humo>(new Trazador_humo(x, y, tv, v));
	return res;
}
