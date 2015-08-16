#include "generador_estructura_niveles.h"
#include "../../herramientas_proyecto/selector_aleatorio.h"
#include <algorithm>
#include <herramientas/log_base/log_base.h>

/**
* TODO: Notas para el generador de salas:
* - Cada sala tendría que tener un spawn point además de sus salidas.
* - El algoritmo no detecta dead ends para darles buenas cosas. Se podría 
* calcular la distancia a las salas que tienen una única salida con respecto
* al inicio para darles unos niveles de bonus o algo. Con respecto a la salida
* o a la llegada, que son los sitios obligatorios a los que hay que ir. Si 
* lo hacemos así tendremos que meternos en pathfinding para no andar en 
* círculos!!!!!
*/


using namespace App_Generador;
using namespace App_Definiciones;

extern DLibH::Log_base LOG;

void Generador_estructura_niveles::construir_sala(int x, int y, direcciones salidas, bool principal, Proto_sala::tipos tipo)
{
	if(!es_pos_libre(x, y))
	{
		throw SalaExisteException(x, y, "La sala en posición ya existe");
	}

	salas.push_back(Proto_sala(x, y, salidas, principal, tipo));
}

direcciones Generador_estructura_niveles::obtener_salida_aleatoria(direcciones salidas)
{
	HerramientasProyecto::Selector_aleatorio_uniforme<direcciones> SAU;
	std::vector<direcciones> vs {direcciones::arriba, direcciones::abajo, direcciones::izquierda, direcciones::derecha};
	for(direcciones t : vs) if( (salidas & t) != direcciones::nada ) SAU.insertar(t);

	if(SAU.size()) return SAU.obtener();
	else return direcciones::nada;
}

void Generador_estructura_niveles::generar_camino_principal(unsigned int c)
{
	LOG<<"Iniciando construccion principal de "<<c<<" salas"<<std::endl;

	unsigned int i=0, x=0, y=0;

	while(i < c)
	{
		construir_sala(x, y, direcciones::nada, true, Proto_sala::tipos::normal);

		//Decidir la siguiente salida...
		direcciones salida=obtener_salida_aleatoria(obtener_libres_adyacentes_para_posicion(x, y));

		//Escoger la información de la siguiente sala...
		switch(salida)
		{
			case direcciones::arriba: --y; break;
			case direcciones::abajo: ++y; break;
			case direcciones::derecha: ++x; break;
			case direcciones::izquierda: --x; break;
			case direcciones::nada: 
				LOG<<"Detectada espiral en proceso de generación de niveles"<<std::endl;
				i=c;	//Nos hemos metido en una espiral... Vamos a finalizar.
			break;
		}

		++i;	
	}

	LOG<<"Iniciando conexión y tipado de salas principales"<<std::endl;
	salas[0].mut_tipo(Proto_sala::tipos::inicio);
	salas[salas.size()-1].mut_tipo(Proto_sala::tipos::fin);

	auto siguiente=salas.begin()+1;

	for(auto& s : salas)
	{
		if(siguiente != salas.end())
		{
			conectar_proto_salas(s, *siguiente);
			++siguiente;
		}
	}
}

bool Generador_estructura_niveles::es_pos_libre(int px, int py)
{
	for(auto& s : salas)
		if(s.es_en_posicion(px, py)) return false;

	return true;
}

Proto_sala& Generador_estructura_niveles::obtener_sala_pos(int px, int py)
{
	for(auto& s : salas)
	{
		if(s.es_en_posicion(px, py)) return s;
	}
	throw SalaNoExisteException(px, py, "No se encuentra la sala en la posición especificada");
}

direcciones Generador_estructura_niveles::base_obtener_adyacentes_para_posicion(int px, int py, bool libre)
{
	struct P{int x, y;};
	P arriba {px, py-1}, abajo {px, py+1}, derecha {px+1, py}, izquierda {px-1, py};

	direcciones resultado=direcciones::nada;
	auto f=[this, libre](P p, direcciones t)
	{
		if(libre)
		{
			if(es_pos_libre(p.x, p.y)) return t;
			return direcciones::nada;
		}
		else 
		{
			if(!es_pos_libre(p.x, p.y)) return t;
			return direcciones::nada;
		}
	};

	resultado=resultado | f(arriba, direcciones::arriba);
	resultado=resultado | f(abajo, direcciones::abajo);
	resultado=resultado | f(derecha, direcciones::derecha);
	resultado=resultado | f(izquierda, direcciones::izquierda);

	return resultado;	
}

void Generador_estructura_niveles::normalizar()
{
	struct F
	{
		int minx, miny;
		void operator()(Proto_sala& p)
		{
			if(p.acc_x() < minx) minx=p.acc_x();
			if(p.acc_y() < miny) miny=p.acc_y();
		}
	}f{0, 0};

	for(Proto_sala& p : salas) f(p);
	for(Proto_sala& p : salas) p.normalizar(abs(f.minx), abs(f.miny));	
}

std::vector<App_Definiciones::tipos::coordenadas_t_dim> Generador_estructura_niveles::obtener_potenciales_conectadas()
{
	using namespace App_Definiciones;
	std::vector<tipos::coordenadas_t_dim> resultado;

	auto f=[this, &resultado](unsigned int x, unsigned int y)
	{
		if(es_pos_libre(x, y)) resultado.push_back(tipos::coordenadas_t_dim(x, y)); 

	};

	for(Proto_sala& p : salas)
	{
		f(p.acc_x()+1, p.acc_y());
		f(p.acc_x()-1, p.acc_y());
		f(p.acc_x(), p.acc_y()+1);
		f(p.acc_x(), p.acc_y()-1);
	}

	std::sort(std::begin(resultado), std::end(resultado));
	auto p=std::unique(std::begin(resultado), std::end(resultado));
	resultado.erase(p, std::end(resultado) );

	return resultado;
}

void Generador_estructura_niveles::generar_salas_secundarias(unsigned int c)
{
	LOG<<"Iniciando construccion de "<<c<<" salas secundarias"<<std::endl;

	unsigned int i=0;
	using namespace HerramientasProyecto;
	
	while(i < c)
	{
		//Obtener todas las libres.
		auto libres=obtener_potenciales_conectadas();

		//Escoger una y construirla.
		Generador_int G(0, libres.size()-1);
		auto coords=libres[G()];
		construir_sala(coords.x, coords.y, direcciones::nada, false, Proto_sala::tipos::normal);

		//Examinar posibles conexiones y conectar.
		direcciones salida=obtener_salida_aleatoria(obtener_ocupadas_adyacentes_para_posicion(coords.x, coords.y));
		auto coords_conexion=coordenadas_desde_posicion_y_direccion(coords, salida);
		conectar_proto_salas(coords, coords_conexion);

		++i;
	}
}

App_Definiciones::tipos::coordenadas_t_dim Generador_estructura_niveles::coordenadas_desde_posicion_y_direccion(App_Definiciones::tipos::coordenadas_t_dim coords, direcciones s)
{
	switch(s)
	{
		case direcciones::arriba: --coords.y; break;
		case direcciones::abajo: ++coords.y; break;
		case direcciones::derecha: ++coords.x; break;
		case direcciones::izquierda: --coords.x; break;
		case direcciones::nada: break;
	}

	return coords;
}

void Generador_estructura_niveles::conectar_proto_salas(App_Definiciones::tipos::coordenadas_t_dim& sala_a, App_Definiciones::tipos::coordenadas_t_dim& sala_b)
{
	auto& sa=obtener_sala_pos(sala_a.x, sala_a.y);
	auto& sb=obtener_sala_pos(sala_b.x, sala_b.y);

	conectar_proto_salas(sa, sb);
}

void Generador_estructura_niveles::conectar_proto_salas(Proto_sala& sala_a, Proto_sala& sala_b)
{
	direcciones val_a=direcciones::nada;
	
	if(sala_a.acc_x()==sala_b.acc_x()+1) //A a la izquierda de b
	{
		val_a=direcciones::izquierda;
	}
	else if(sala_a.acc_x()==sala_b.acc_x()-1) //A a la derecha de b
	{
		val_a=direcciones::derecha;
	}
	else if(sala_a.acc_y()==sala_b.acc_y()+1) //A abajo de b.
	{
		val_a=direcciones::arriba;
	}
	else if(sala_a.acc_y()==sala_b.acc_y()-1) //A encima de b.
	{
		val_a=direcciones::abajo;
	}
	
	sala_a.mut_salidas(sala_a.acc_salidas() | val_a);
	sala_b.mut_salidas(sala_b.acc_salidas() | obtener_direccion_contraria(val_a));
}
