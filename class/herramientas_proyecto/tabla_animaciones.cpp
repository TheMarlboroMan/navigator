#include "tabla_animaciones.h"

using namespace HerramientasProyecto;
			
/**
* Ajusta el valor "momento_aparición" de cada uno de los frames con respecto
* al tiempo general de la aplicación.
*/

void Animacion::reajustar_tiempo_frames()
{
	duracion_total=0;
	for(auto& l: lineas)
	{
		duracion_total+=l.duracion;
		l.momento_aparicion=duracion_total;
	}
}

/**
* Devuelve la línea que corresponde para el tiempo t en el ciclo de la 
* animación.
*/

const Linea_animacion& Animacion::obtener_para_tiempo_animacion(float t)
{
	if(lineas.size()==1) return lineas.at(0);
	else
	{
		float transformado=fmod(t, duracion_total);
		for(const Linea_animacion& fr : lineas)
		{
			if(transformado <= fr.momento_aparicion) return fr;
		}
		return lineas.at(0);
	}
}

//Aquí definimos los métodos de la tabla de animaciones.

Tabla_animaciones::Tabla_animaciones(const Tabla_sprites& t)
	:tabla_sprites(t)
{	

}

Tabla_animaciones::Tabla_animaciones(const Tabla_sprites& t, const std::string& ruta)
	:tabla_sprites(t)
{	
	cargar(ruta);
}

void Tabla_animaciones::cargar(const std::string& ruta)
{
	DLibH::Lector_txt L(ruta, '#');

	if(!L)	
	{
		LOG<<"ERROR: Para Tabla_animaciones no se ha podido abrir el archivo "<<ruta<<std::endl;
		throw std::runtime_error("Imposible localizar archivo de animación.");
	}
	else
	{
		std::string linea;
		const char inicio_titulo='*';
		const char inicio_cabecera='!';
		size_t id=0;
		Animacion animacion;

		auto insertar_anim=[this](Animacion animacion, size_t id)
		{
			animacion.reajustar_tiempo_frames();
			animaciones[id]=animacion;					
		};

		try
		{
			while(true)
			{
				linea=L.leer_linea();
				if(!L) 
				{	
					//Insertar la última animación...
					if(animacion) insertar_anim(animacion, id);
					break;
				}

				const char inicio=linea[0];
				switch(inicio)
				{
					case inicio_titulo: 
						if(animacion) insertar_anim(animacion, id);
						animacion=Animacion(); //Reset animación...
						animacion.nombre=linea.substr(1);
					break;
					case inicio_cabecera: 
						id=interpretar_como_cabecera(linea.substr(1)); 
					break;
					default: 
						interpretar_como_linea(linea, animacion); 
					break;
				}
			}
		}
		catch(std::runtime_error& e)
		{
			LOG<<e.what()<<" : Línea "<<L.obtener_numero_linea()<<" ["<<linea<<"]. Cancelando."<<std::endl;
			throw e;
		}
		catch(std::out_of_range& e)
		{
			LOG<<e.what()<<" : Línea "<<L.obtener_numero_linea()<<" ["<<linea<<"]. Cancelando."<<std::endl;
			throw e;
		}
	}
}

size_t Tabla_animaciones::interpretar_como_cabecera(const std::string& linea)
{
	const char separador='\t';
	const std::vector<std::string> valores=DLibH::Herramientas::explotar(linea, separador);
	if(valores.size()==1)
	{
		int id=std::atoi(valores[0].c_str());
		return id;
	}
	else
	{
		throw std::runtime_error("Error al leer cabecera de animación.");
	}
}

void Tabla_animaciones::interpretar_como_linea(const std::string& linea, Animacion& animacion)
{
	const char separador='\t';
	std::vector<std::string> valores=DLibH::Herramientas::explotar(linea, separador);
	if(valores.size()==2)
	{
		int duracion=std::atoi(valores[0].c_str());
		int indice_frame=std::atoi(valores[1].c_str());

		try
		{
			const auto& frame=tabla_sprites.obtener(indice_frame);

			float dur=(float)duracion / 1000.f;
			animacion.duracion_total+=dur;
			animacion.lineas.push_back(Linea_animacion{dur, 0.0f, frame});
			animacion.reajustar_tiempo_frames();
		}
		catch(std::out_of_range& e)
		{
			LOG<<e.what()<<" : no se localiza el indice frame "<<indice_frame<<" para interpretar como línea"<<std::endl;
			throw e;
		}
	}
	else
	{
		throw std::runtime_error("Error al leer cabecera de animación.");
	}
}
