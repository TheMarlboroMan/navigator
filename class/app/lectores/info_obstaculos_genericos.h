#ifndef INFO_OBSTACULOS_GENERICOS_H
#define INFO_OBSTACULOS_GENERICOS_H

#include <map>
#include <vector>
#include <string>
#include <herramientas/herramientas/herramientas.h>
#include <herramientas/lector_txt/lector_txt.h>
#include <herramientas/log_base/log_base.h>

extern DLibH::Log_base LOG;

namespace App_Lectores
{

class Info_obstaculos_genericos
{
	///////////////////////
	//Interface pública.

	public:

	struct Info
	{
		int w, h, indice_animacion;
	};


						Info_obstaculos_genericos(const std::string&);
	void					cargar(const std::string&);
	const Info&				obtener(size_t) const;
		
	///////////////////////
	//Internas...
	
	private:

	std::map<unsigned int, Info>		info;
};

}

#endif
