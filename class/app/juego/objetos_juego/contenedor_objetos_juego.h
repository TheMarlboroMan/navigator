#ifndef CONTENEDOR_OBJETOS_JUEGO_H
#define CONTENEDOR_OBJETOS_JUEGO_H

#include <vector>
#include <memory>
#include <functional>
#include "../../interfaces/objeto_juego_i.h"
#include "../../interfaces/bonus_i.h"
#include "../../interfaces/con_turno_i.h"
#include "../../interfaces/disparable_i.h"
#include "../../interfaces/disparador_i.h"
#include "../../interfaces/representable_i.h"
#include "../../interfaces/colisionable_i.h"
#include "../../interfaces/sonoro_i.h"
#include "entrada.h"
#include "salida.h"
#include "posicion_inicial.h"
/**
* Estructura diseñada para albergar objetos de juego. Se le pasaría a las salas
* para que puedan tener objetos de juego. La tarea de llenado se haría con
* las factorías.
*/

namespace App_Juego_ObjetoJuego
{
	struct Contenedor_objetos
	{
											Contenedor_objetos();
		typedef std::vector<std::shared_ptr<App_Interfaces::Objeto_juego_I> > Vsptr_Objeto_juego_I;

		Vsptr_Objeto_juego_I							objetos_juego;	//Todos los objetos de juego van aquí. Es el vector "real" donde se hacen deletes.

		/**
		* El resto de vectores contendrían "copias" del original, por así decirlo.
		*/

		std::vector<std::shared_ptr<App_Interfaces::Bonus_I>>			bonus;
		std::vector<std::shared_ptr<App_Interfaces::Con_turno_I>>		con_turno;
		std::vector<std::shared_ptr<App_Interfaces::Disparable_I>>		disparables;
		std::vector<std::shared_ptr<App_Interfaces::Disparador_I>>		disparadores;
		std::vector<std::shared_ptr<App_Interfaces::Representable_I>>		representables;
		std::vector<std::shared_ptr<App_Interfaces::Colisionable_I>>		colisionables;
		std::vector<std::shared_ptr<App_Interfaces::Sonoro_I>>			sonoros;

		/**
		* Además, las entradas del nivel y posiciones iniciales y finales.
		*/

		std::vector<Entrada>							entradas;
		App_Definiciones::direcciones 						direcciones_entradas;

		//Podrían ser unique, aunque la salida mejor dejarla shared porque tiene referencias en colisionable y representable.
		std::shared_ptr<Posicion_inicial>					posicion_inicial;
		std::shared_ptr<Salida>							salida;


		/**
		* Métodos...
		*/
		void 									insertar_entrada(const Entrada& e); /** std::logic_error cuando existe una entrada en la posición. */
		void									sumar_variante(const Contenedor_objetos&);
		size_t									limpiar_para_borrar();

		private:

		template<typename T> size_t ayudante_borrar(std::vector<std::shared_ptr<T>>& v)
		{
			size_t	res=0;
			auto 	ini=std::begin(v),
				fin=std::end(v);
	
			while(ini < fin)
			{
				if(ini->get()->es_borrar())
				{
					ini=v.erase(ini);
					fin=std::end(v);
					++res;
				}
				else
				{
					++ini;
				}		
			}
			return res;
		}

	};
}

#endif
