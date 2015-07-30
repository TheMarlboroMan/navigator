#ifndef GENERADOR_ESTRUCTURA_NIVELES_H
#define GENERADOR_ESTRUCTURA_NIVELES_H

#include "proto_sala.h"
#include "../definiciones/definiciones.h"
#include <vector>
#include <stdexcept>

namespace App_Generador
{

class Generador_estructura_niveles
{
	//////////////
	//Definiciones
	public:

	private:

	struct SalaNoExisteException:public std::logic_error
	{		
		public:
		int x, y;
		SalaNoExisteException(int px, int py, const std::string& m)
			:logic_error(m), x(px), y(py)
		{}
	};

	struct SalaExisteException:public std::logic_error
	{		
		public:
		int x, y;
		SalaExisteException(int px, int py, const std::string& m)
			:logic_error(m), x(px), y(py)
		{}
	};

	//////////////
	//Propiedades
	private:
	std::vector<Proto_sala> salas;

	//////////////
	//Métodos privados
	private:
	
	/**
	* @param int px
	* @param int py
	* @return Proto_sala&
	* @throw SalaNoExisteException
	*/

	Proto_sala& obtener_sala_pos(int px, int py);

	/**
	* @param int px
	* @param int py
	* @return bool
	*/

	bool es_pos_libre(int px, int py);

	/**
	* @param int px
	* @param int px
	* @return direcciones
	* Devuelve las direcciones en las que hay huecos libres para la sala.
	*/

	App_Definiciones::direcciones obtener_libres_adyacentes_para_posicion(int px, int py)
	{
		return base_obtener_adyacentes_para_posicion(px, py, true);
	}

	/**
	* @param int px
	* @param int px
	* @return App_Definiciones::direcciones
	* Devuelve las direcciones en las que hay huecos ocupados para las coordenadas.
	*/

	App_Definiciones::direcciones obtener_ocupadas_adyacentes_para_posicion(int px, int py)
	{
		return base_obtener_adyacentes_para_posicion(px, py, false);
	}

	/**	
	* Base para las dos anteriores...
	*/
	App_Definiciones::direcciones base_obtener_adyacentes_para_posicion(int px, int py, bool libre);

	/**
	* @param int x : posición x
	* @param int y : posición y
	* @param App_Definiciones::direcciones salidas
	* @param bool principal
	* @param Proto_sala::tipos tipo
	* @throw SalaExisteException
	*/

	void construir_sala(int x, int y, App_Definiciones::direcciones salidas, bool principal, Proto_sala::tipos tipo);

	/**	
	* @param App_Definiciones::direcciones
	* @return App_Definiciones::direcciones.
	*/

	App_Definiciones::direcciones obtener_salida_aleatoria(App_Definiciones::direcciones salidas);

	/**
	* @return std::vector<coordenadas_t_dim>
	* Obtiene un vector con todas las posibles posiciones en las que
	* se podría añadir una sala.
	*/

	std::vector<App_Definiciones::tipos::coordenadas_t_dim> obtener_potenciales_conectadas();

	/**
	* @param coordenadas_t_dim coordenadas
	* @param App_Definiciones::direcciones s
	* @return coordenadas_t_dim
	* Devuelve el par de de coordenadas que estarían en la dirección 
	* especificada a partir de las coordenadas especificadas.
	*/

	App_Definiciones::tipos::coordenadas_t_dim coordenadas_desde_posicion_y_direccion(App_Definiciones::tipos::coordenadas_t_dim coords, App_Definiciones::direcciones s);

	/**
	* @param coordenadas_t_dim& sala_a
	* @param coordenadas_t_dim& sala_b
	* Si las salas son adyacentes actualiza su valor de salidas para
	* que estén conectadas.
	*/

	void conectar_proto_salas(App_Definiciones::tipos::coordenadas_t_dim& sala_a, App_Definiciones::tipos::coordenadas_t_dim& sala_b);
	void conectar_proto_salas(Proto_sala& sala_a, Proto_sala& sala_b);  

	//////////////
	//Interface pública
	public:

	Generador_estructura_niveles() {}

	/**
	* @param unsigned int c
	* @throw SalaExisteException cuando hay un fallo en la generación.
	* @throw SelectorAleatorioException cuando hay un fallo en la generación.
	* @throw std::logic_error, para cualquiera de las de arriba.
	*
	* Inicia la generación del camino principal compuesto de tantas salas
	* como especifique el parámetro.
	*/

	void generar_camino_principal(unsigned int c);

	/**
	* @param unsigned int c
	* Inicia la generación de tantas salas secundarias como se indique.
	*/

	void generar_salas_secundarias(unsigned int c);

	/**
	* Hace que la sala en la esquina superior izquierda sean las coordenadas
	* 0,0 y ajusta el resto.
	*/

	void normalizar();

	const std::vector<Proto_sala>& acc_proto_salas() const {return salas;}
};
}

#endif
