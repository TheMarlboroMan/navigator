#ifndef EFECTO_COLISION_I_H
#define EFECTO_COLISION_I_H

#include "objeto_juego_i.h"
#include "espaciable.h"
#include "efecto_colision_recogedor_i.h"

namespace App_Interfaces
{
class Efecto_colision_I:
	public virtual Objeto_juego_I
{
	public:

				~Efecto_colision_I();
	virtual void		efecto_colision(App_Interfaces::Efecto_colision_recogedor_I&)=0;
	virtual bool		es_colision_para(const App_Interfaces::Espaciable&)const=0;
};
}

#endif
