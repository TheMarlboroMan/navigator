#include "representador.h"

using namespace App_Graficos;

Representador::Representador()
{

}

Representador::~Representador()
{

}

unsigned int Representador::generar_vista(
	DLibV::Pantalla& pantalla, 
	DLibV::Camara& camara, 
	const std::vector<const Representable *>& v)
{
	unsigned int total=0;

	for(const Representable * r : v)
	{
		r->transformar_bloque(bloque_transformacion);
		if(bloque_transformacion.rep->volcar(pantalla, camara)) ++total;
	}

	return total;
}

unsigned int Representador::generar_vista(
	DLibV::Pantalla& pantalla, 
	const std::vector<const Representable *>& v)
{
	unsigned int total=0;

	for(const Representable * r : v)
	{
		r->transformar_bloque(bloque_transformacion);
		if(bloque_transformacion.rep->volcar(pantalla)) ++total;
	}

	return total;
}
