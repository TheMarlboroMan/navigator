#ifndef CONTENEDOR_HERRAMIENTAS_H
#define CONTENEDOR_HERRAMIENTAS_H

#include <vector>
#include <memory>

namespace App_Juego_Contenedores
{

template<typename T> size_t ayudante_borrar(std::vector<std::shared_ptr<T>>& v)
{
	size_t	res=0;
	auto 	ini=std::begin(v);

	while(ini < std::end(v))
	{
		if(ini->get()->es_borrar())
		{
			ini=v.erase(ini);
			++res;
		}
		else
		{
			++ini;
		}		
	}
	return res;
}

}

#endif
