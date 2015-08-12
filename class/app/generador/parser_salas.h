#ifndef PARSER_SALAS_H
#define PARSER_SALAS_H

#include <string>
#include "../definiciones/definiciones.h"
#include "../niveles/sala.h"

namespace App_Generador
{

class Parser_salas
{
	//////////////////////
	//Interface pública

	public:

					Parser_salas();
	void 				parsear_fichero(const std::string& ruta, App_Definiciones::tipos::t_dim pos_x, App_Definiciones::tipos::t_dim pos_y);
	App_Niveles::Sala&		acc_sala() {return sala;}

	private:

	bool				interpretar_estado(const std::string& linea);
	void 				interpretar_linea_como_rejilla(const std::string& linea, App_Definiciones::tipos::t_dim pos_x, App_Definiciones::tipos::t_dim pos_y);
	void				interpretar_linea_como_celdas(const std::string& linea);
	void				interpretar_linea_como_objeto(const std::string& linea);
	int				toi(const std::string& s) {return std::atoi(s.c_str());};

	enum class 			t_estados {nada, estructura, info, rejilla, celdas, logica, objetos, fin};
	
	t_estados 			estado;
	static const std::string 	TIPO_ESTRUCTURA;
	static const std::string 	TIPO_FIN_ESTRUCTURA;
	static const std::string 	TIPO_INFO;
	static const std::string 	TIPO_REJILLA;
	static const std::string 	TIPO_CELDAS;
	static const std::string 	TIPO_CAMARA;
	static const std::string 	TIPO_LOGICA;
	static const std::string 	TIPO_OBJETOS;

	App_Niveles::Sala 		sala;


};

}

#endif
