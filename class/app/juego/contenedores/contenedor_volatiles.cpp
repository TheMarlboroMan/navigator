#include "contenedor_volatiles.h"

using namespace App_Juego_Contenedores;

void Contenedor_volatiles::fusionar_con(Contenedor_volatiles& c)
{
	std::move(std::begin(c.proyectiles_jugador), std::end(c.proyectiles_jugador), std::back_inserter(proyectiles_jugador));
	std::move(std::begin(c.proyectiles_enemigos), std::end(c.proyectiles_enemigos), std::back_inserter(proyectiles_enemigos));
	std::move(std::begin(c.particulas), std::end(c.particulas), std::back_inserter(particulas));
	std::move(std::begin(c.trazadores), std::end(c.trazadores), std::back_inserter(trazadores));
}

size_t Contenedor_volatiles::limpiar_para_borrar()
{
	size_t	res=0;
	res+=ayudante_borrar(proyectiles_jugador);
	res+=ayudante_borrar(proyectiles_enemigos);
	res+=ayudante_borrar(particulas);
	res+=ayudante_borrar(trazadores);
	return res;
}

size_t Contenedor_volatiles::size() const
{
	size_t	res=proyectiles_jugador.size()+proyectiles_enemigos.size()+particulas.size()+trazadores.size();
	return res;
}

void Contenedor_volatiles::vaciar()
{
	proyectiles_jugador.clear();
	proyectiles_enemigos.clear();
	particulas.clear();
	trazadores.clear();
}
