#ifndef PARTICULA_NUMERO_H
#define PARTICULA_NUMERO_H

#include <map>
#include <video/representacion/representacion_grafica/representacion_texto/representacion_texto_auto.h>

#include "particula_movil_base.h"
#include "../../definiciones/animaciones.h"
#include "../../definiciones/definiciones.h"
#include "../../recursos.h"

/**
* Un número que sube, indicando daño hecho, por ejemplo.
*/

namespace App_Juego_ObjetoJuego
{

class Particula_numero:
	public Particula_movil_base
{
	//////////////////
	//Interface pública...
	public:
						Particula_numero(float x, float y, float tv, size_t val, App_Definiciones::colores::colores_texto col, const DLibH::Vector_2d& v);
	static void				preparar_representacion(size_t numero, const DLibV::Representacion_texto_auto_dinamica& rep) {textos.insert(std::make_pair(numero, rep));}
	bool					debe_preparar_representacion(size_t numero) const {return textos.count(numero);}

	//////////////
	// Implementación de Representable_I
	public:

	virtual unsigned int	 		obtener_ciclos_representable()const;
	virtual unsigned short int 		obtener_profundidad_ordenacion()const;
	virtual void 				transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const;

	//////////////
	// Implementación de Con_turno_I
	public:

	virtual void 				turno(App_Interfaces::Contexto_turno_I&);

	/////////////////
	//Internas.
	private:

	size_t										numero;
	App_Definiciones::colores::colores_texto					color;
	static std::map<size_t, DLibV::Representacion_texto_auto_dinamica>		textos;
};
}

#endif
