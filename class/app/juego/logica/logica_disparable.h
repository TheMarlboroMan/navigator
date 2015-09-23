#ifndef LOGICA_DISPARABLE_H
#define LOGICA_DISPARABLE_H

#include <vector>
#include <memory>

#include "../../interfaces/disparable_i.h"
#include "../objetos_juego/proyectil_base.h"

/**
* Lógica para los objetos que implementen la interface "Disparable_I".
* Controla si han recibido impactos.
*/

namespace App_Graficos
{
class Barra_indicadora;
}

namespace App_Juego_Logica
{

class Logica_disparable
{
	//Definición interna...
	private:
	struct contexto:
		public App_Interfaces::Disparable_contexto_I,
		public App_Interfaces::Generador_objetos_juego_I
	{
		struct marcador
		{
			size_t numero;
			float x, y;
		};

		std::vector<marcador> 		marcadores;

		struct info_barra
		{
			float			salud_max=0.f, salud_actual=0.f;
			std::string		nombre;
			bool 			activa=false;
		}info_barra;

		void				asignar_barra(float sm, float sa, const std::string& n);
		void				insertar_marcador(float val, float x, float y);
		virtual	void			generar_objetos(App_Interfaces::Factoria_objetos_juego_I& foj);
	}contexto;

	////////////////////////
	//Interface pública.
	public:

							Logica_disparable(std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base >>&);
	virtual void 					procesar(std::vector<App_Interfaces::Disparable_I *>&);
	App_Interfaces::Generador_objetos_juego_I&	acc_generador_particulas() {return contexto;}
	bool						hay_numeros_por_generar() const {return contexto.marcadores.size();}
	void						actualizar_barra(App_Graficos::Barra_indicadora&);
	
	

	/////////////////////////
	//Propiedades privadas.
	private:

	std::vector<std::shared_ptr<App_Juego_ObjetoJuego::Proyectil_base>>& proyectiles_jugador;
};
}

#endif
