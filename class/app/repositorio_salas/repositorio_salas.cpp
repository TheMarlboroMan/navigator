#include "repositorio_salas.h"

#include <algorithm>
#include <stdexcept>
#include <herramientas/lector_txt/lector_txt.h>

using namespace App_RepositorioSalas;

Repositorio_salas::Repositorio_salas()
{
	iniciar_mapa();
}

/**
* Se extrae el primer item de la lista y se le añade un uso.
*/

const std::string Repositorio_salas::obtener_ruta_sala(App_Definiciones::direcciones dir)
{
	std::vector<Item_repositorio>& vec=mapa_rutas.at(dir);
	auto item=vec.begin();
	item->sumar_uso();
	std::sort(vec.begin(), vec.end());
	return item->acc_ruta();
}

/**
* Inicializa el mapa de rutas creando tantas claves como posibilidades de
* dirección distintas hay y montando dentro un vector de "Item_repositorio".
*/

void Repositorio_salas::iniciar_mapa()
{
	using namespace App_Definiciones;
	std::vector<direcciones> dr = {
		/* 1  */ direcciones::arriba,
		/* 2  */ direcciones::derecha,
		/* 3  */ direcciones::arriba | direcciones::derecha,
		/* 4  */ direcciones::abajo,
		/* 5  */ direcciones::arriba | direcciones::abajo,        
		/* 6  */ direcciones::derecha | direcciones::abajo,
		/* 7  */ direcciones::derecha | direcciones::abajo | direcciones::arriba,
		/* 8  */ direcciones::izquierda,
		/* 9  */ direcciones::izquierda | direcciones::arriba,
		/* 10  */ direcciones::izquierda | direcciones::derecha,
		/* 11  */ direcciones::izquierda | direcciones::derecha | direcciones::arriba,
		/* 12  */ direcciones::izquierda | direcciones::abajo,
		/* 13  */ direcciones::izquierda | direcciones::abajo | direcciones::arriba,
		/* 14  */ direcciones::izquierda | direcciones::abajo | direcciones::derecha,
		/* 15  */ direcciones::izquierda | direcciones::abajo | direcciones::derecha | direcciones::arriba};

	
	for(auto d : dr)
	{
		std::vector<Item_repositorio> v;
		mapa_rutas[d]=v;
	}
}

void Repositorio_salas::iniciar(const std::string& r, const App_Lectores::Info_obstaculos_genericos& iog)
{
	//Abrir el fichero con la ruta...
	DLibH::Lector_txt L(r, '#');

	if(!L)
	{
		LOG<<"ERROR: Imposible localizar repositorio de salas en "<<r<<std::endl;
		throw std::runtime_error("Error al iniciar repositorio de salas: repositorio no localizado.");
	}
	else
	{	
		std::string linea;

		while(true)
		{
			linea=L.leer_linea();
			if(!L) break;

			LOG<<"Procesando "<<linea<<std::endl;

			App_Generador::Parser_salas p;
			p.parsear_fichero(linea, iog);

			if(!p.comprobar_validez_sala())
			{
				LOG<<"ERROR: La sala no pasa la validación : "<<linea<<std::endl;
				throw std::runtime_error("Error al iniciar repositorio de salas: error de validación.");
			}

			mapa_rutas[p.acc_direcciones_entradas()].push_back(linea);
		}
	}

	//Comprobamos que hay mapas en todos los tipos y los reordenamos al azar.
	int dir=1;	//Se usará para llevar la cuenta si falla en un directorio concreto.

	for(auto& d : mapa_rutas)
	{
		auto& v=d.second;
		if(! v.size())
		{
			LOG<<"ERROR: Al menos una posible dirección no tiene salas ["<<dir<<"]"<<std::endl;
			throw std::runtime_error("Error al iniciar repositorio de salas: error de integridad.");
		}

		std::random_shuffle(v.begin(), v.end());
		++dir;
	}
}

