#ifndef BORRABLE_I_H
#define BORRABLE_I_H

////
//TODO: No es tanto una "interface" como una "faceta".

namespace App_Interfaces
{
class Borrable_I
{
	public:
			Borrable_I():borrar(false) {}
	virtual 	~Borrable_I() {}
	bool 		es_borrar() const {return borrar;}
	void 		mut_borrar(bool v) {borrar=v;}	

	private:
	bool 		borrar;
};
}

#endif
