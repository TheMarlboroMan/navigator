#ifndef BOOTSTRAP_APLICACION
#define BOOTSTRAP_APLICACION

#include "../class/controladores/director_estados.h"
#include "../class/framework/derivada/kernel.h"
#include "../class/app/repositorio_salas/repositorio_salas.h"

namespace App
{

struct parametros_test
{
	bool valido=false;
	int tipo=0, nivel=0, variante=0;
};

void loop_aplicacion(Kernel_app& kernel);
parametros_test obtener_parametros_test(DLibH::Controlador_argumentos& CARG);

}

#endif
