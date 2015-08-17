#include "espaciable.h"

using namespace App_Interfaces;

Espaciable::Espaciable()
{

}

Espaciable::~Espaciable()
{

}

bool Espaciable::en_colision_con(const Espaciable& e, bool roce_es_colision) const
{
	return copia_caja().es_en_colision_con(e.copia_caja(), roce_es_colision);
}

Espaciable::t_caja Espaciable::copia_caja_desplazada(float x, float y) const
{
	auto c=copia_caja();
	c.origen.x+=x;
	c.origen.y+=y;
	return c;
}

void Espaciable::establecer_posicion(const Espaciable& e)
{
	mut_x_caja(e.acc_espaciable_x());	
	mut_y_caja(e.acc_espaciable_y());
}

void Espaciable::establecer_posicion(float x, float y)
{
	mut_x_caja(x);	
	mut_y_caja(y);
}

DLibH::Vector_2d Espaciable::obtener_vector_para(const Espaciable& a, const Espaciable& b) 
{
	float ax=a.acc_espaciable_x() + (a.acc_espaciable_w() / 2);
	float ay=a.acc_espaciable_y() + (a.acc_espaciable_h() / 2);
	float bx=b.acc_espaciable_x() + (b.acc_espaciable_w() / 2);
	float by=b.acc_espaciable_y() + (b.acc_espaciable_h() / 2);

	return Vector_2d::obtener_para_puntos(bx, by, ax, ay);
}

