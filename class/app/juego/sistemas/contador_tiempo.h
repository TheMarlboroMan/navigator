#ifndef CONTADOR_TIEMPO_H
#define CONTADOR_TIEMPO_H

#include <string>

namespace App_Juego_Sistemas
{
class Contador_tiempo
{
	//////////////////////
	//Propiedades
	private:
	float tiempo_restante;

	//////////////////////
	//Interface pública
	public:
	Contador_tiempo(float c=0)
		:tiempo_restante(c)
	{}

	/**
	* @param float delta : la cantidad de tiempo en segundos que ha pasado.
	*/

	void turno(float delta);
	
	/**
	* @return std::string
	* Genera una cadena con el tiempo restante formateado como MM:SS:DD
	*/

	std::string formatear_tiempo_restante();

	/**
	* @return bool
	* Indica si queda tiempo restante en el contador.
	*/

	bool es_tiempo_restante() const {return tiempo_restante > 0.0;}

	/** 
	* @param float v
	* Suma la cantidad pasada al tiempo restante...
	*/

	void sumar_tiempo(float v)
	{
		tiempo_restante+=v;
	}

	float acc_tiempo_restante() const {return tiempo_restante;}
	void mut_tiempo_restante(float v) {tiempo_restante=v;}
};
}

#endif
