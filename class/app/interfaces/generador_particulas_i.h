#ifndef GENERADOR_PARTICULAS_I
#define GENERADOR_PARTICULAS_I

#include <memory>
#include <vector>
#include "../juego/prototipos/definicion_particula.h"
#include "objeto_juego_i.h"

namespace App_Interfaces
{
/**
* Interface para los objetos que generan particulas... No es tanto una
* interface como una clase base para que todos aquellos que generen particulas
* podamos cogerlos por el mismo asa.
*/

class Generador_particulas_I:
	public virtual Objeto_juego_I
{
	public:

	typedef std::vector<std::shared_ptr<App_Juego_Prototipos::Definicion_particula>> vDefinicionParticula;
	typedef std::shared_ptr<App_Juego_Prototipos::Definicion_particula> sptrDefinicionParticula;

	bool							hay_particulas();
	void							reset_particulas();
	vDefinicionParticula&					acc_particulas();
	void							insertar_particula(sptrDefinicionParticula);

	private:

	vDefinicionParticula					prototipos;
	
};
}

#endif
