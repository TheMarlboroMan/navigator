#include "item_repositorio.h"

using namespace App_RepositorioSalas;

Item_repositorio::Item_repositorio(const std::string& r)
	:ruta(r), cuenta_usos(0)
{

}

void Item_repositorio::reset_cuenta()
{
	cuenta_usos=0;
}

void Item_repositorio::sumar_uso()
{
	++cuenta_usos;
}
