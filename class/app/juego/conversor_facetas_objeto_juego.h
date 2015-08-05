#ifndef CONVERSOR_FACETAS_OBJETO_JUEGO_H
#define CONVERSOR_FACETAS_OBJETO_JUEGO_H

#include <vector>
#include <memory>
#include "../interfaces/objeto_juego_i.h"
#include "../interfaces/borrable_i.h"
#include "../graficos/representable.h"

namespace App_Juego
{

class Conversor_facetas_objeto_juego
{
	/////////////////////////////////////
	//Interface publica:
	public:

	//TODO: Quizás separar en dos métodos, uno que devuelva y otro 
	static void	extraer_representables(const std::vector<std::shared_ptr<App_Interfaces::Objeto_juego_I> >, std::vector<const App_Graficos::Representable *>&);
	static void	extraer_borrables(const std::vector<std::shared_ptr<App_Interfaces::Objeto_juego_I> >, std::vector<const App_Interfaces::Borrable_I *>&);

	/////////////////////////////////////
	//Privados:
	private:
			Conversor_facetas_objeto_juego();
};

}

#endif
