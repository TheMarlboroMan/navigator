#include "info_obstaculos_genericos.h"

using namespace App_Lectores;

Info_obstaculos_genericos::Info_obstaculos_genericos(const std::string& ruta)
{
	cargar(ruta);
}

void Info_obstaculos_genericos::cargar(const std::string& ruta)
{
	DLibH::Lector_txt L(ruta, '#');

	if(!L)
	{
		LOG<<"ERROR: Imposible localizar fichero info de obstáculos genéricos en "<<ruta<<std::endl;
		throw std::runtime_error("Imposible localizar info de obstáculos genéricos");
	}
	else
	{	
		std::string linea;
		auto toi=[](const std::string& s) {return std::atoi(s.c_str());};

		while(true)
		{
			linea=L.leer_linea();
			if(!L) break;
			std::vector<std::string> valores=Herramientas::explotar(linea, '\t');

			if(valores.size() != 4)
			{
				LOG<<"ERROR: Línea de obstáculos genéricos malformada : "<<linea<<std::endl;
				throw std::runtime_error("Línea de obstáculos genéricos malformada");
			}

			size_t indice=toi(valores[0]);
			if(info.count(indice)) 
			{
				LOG<<"ERROR: Indice de obstáculos genéricos "<<indice<<" ya existe en : "<<linea<<std::endl;
				throw std::runtime_error("Indice de obstáculos genéricos repetido");
			}

			info[indice]=Info{toi(valores[1]), toi(valores[2]), toi(valores[3])};
		}
	}
}

const Info_obstaculos_genericos::Info& Info_obstaculos_genericos::obtener(size_t indice) const
{
	return info.at(indice);
}
