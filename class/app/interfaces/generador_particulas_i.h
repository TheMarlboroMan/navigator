#ifndef GENERADOR_PARTICULAS_I
#define GENERADOR_PARTICULAS_I

#include <memory>
#include <vector>
#include "../juego/particulas/definicion_particula.h"

namespace App_Interfaces
{
/**
* Interface para los objetos que generan particulas... No es tanto una
* interface como una clase base para que todos aquellos que generen particulas
* podamos cogerlos por el mismo asa.
*/

class Generador_particulas_I
{
	public:

	typedef std::vector<std::shared_ptr<App_Juego_Particulas::Definicion_particula>> vDefinicionParticula;
	typedef std::shared_ptr<App_Juego_Particulas::Definicion_particula> sptrDefinicionParticula;

	static bool							hay_prototipos();
	static void							reset_prototipos();
	static vDefinicionParticula&					acc_prototipos();

	void								insertar_prototipo(sptrDefinicionParticula);

	private:

	static vDefinicionParticula					prototipos;
	
};
}

#endif
