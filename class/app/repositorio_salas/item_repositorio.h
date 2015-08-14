#ifndef ITEM_REPOSITORIO_H
#define ITEM_REPOSITORIO_H

#include <string>

namespace App_RepositorioSalas
{

class Item_repositorio
{
	///////////////////
	//Interface pública.
	public:

				Item_repositorio(const std::string&);
	const std::string&	acc_ruta() const {return ruta;}
	int			acc_cuenta_usos() const {return cuenta_usos;}

	void			reset_cuenta();
	void			sumar_uso();
	bool 			operator<(const Item_repositorio& o) const {return cuenta_usos < o.cuenta_usos;}

	///////////////////
	//Internas de la clase...
	private:

	std::string 		ruta;
	int 			cuenta_usos;
};

}

#endif
