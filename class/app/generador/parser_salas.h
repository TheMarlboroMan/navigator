#ifndef PARSER_SALAS_H
#define PARSER_SALAS_H

#include <string>
#include <vector>
#include "../definiciones/definiciones.h"
#include "../niveles/sala.h"
#include "factoria_objetos_juego.h"

namespace App_Generador
{

/**
* El parser de salas. Un aspecto importante es que tiene un vector de contenedor
* de objetos para representar las diferentes variaciones de las salas. Por
* convención interna, la primera "variación" será la que tenga entradas, salidas
* y cosas comunes. El resto de variaciones serían las variantes de las salas.
*/

class Parser_salas
{
	//////////////////////
	//Interface pública

	public:

	enum class tipo_sala 
	{
		normal, 
		inicio, 
		fin
	}; //El tipo de sala determinará la unión que se haga de las variantes.

								Parser_salas();
	void 							parsear_fichero(const std::string& ruta);
	App_Niveles::Sala&					acc_sala() {return sala;}
	bool							comprobar_validez_sala() const;
	size_t							cuenta_contenedores() {return contenedores.size();}
	void							generar_variante_sala(size_t, tipo_sala);
	App_Definiciones::direcciones 				acc_direcciones_entradas() const {return contenedores.front().direcciones_entradas;}	//Para el repositorio, que pueda obtener la información sin generar la variante de la sala.

	private:

	bool							interpretar_estado(const std::string& linea, Factoria_objetos_juego& factoria);
	void 							interpretar_linea_como_rejilla(const std::string& linea);
	void							interpretar_linea_como_celdas(const std::string& linea);
	void							interpretar_linea_como_objeto(const std::string& linea, Factoria_objetos_juego&);
	int							toi(const std::string& s) {return std::atoi(s.c_str());};

	enum class 						t_estados {nada, estructura, info, rejilla, celdas, logica, objetos, fin};
	
	enum class destino_celdas {nada, logica, decoracion};

	destino_celdas						d_celdas;
	t_estados 						estado;
	static const std::string 				TIPO_ESTRUCTURA;
	static const std::string 				TIPO_FIN_ESTRUCTURA;
	static const std::string 				TIPO_INFO;
	static const std::string 				TIPO_REJILLA;
	static const std::string 				TIPO_CELDAS;
	static const std::string 				TIPO_CAMARA;
	static const std::string 				TIPO_LOGICA;
	static const std::string 				TIPO_OBJETOS;

	App_Niveles::Sala 					sala;
	std::vector<App_Juego_Contenedores::Contenedor_objetos>	contenedores;


};

}

#endif
