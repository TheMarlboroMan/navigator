#ifndef MOVIL_H
#define MOVIL_H

/*Modelo de cosa que se mueve en el espacio...  En todo caso, esta es la base 
para el cálculo de movimiento y tiene algunas cosas de gravedad también.
*/

#include <libDan2.h>

namespace App_Interfaces
{

class Movil
{
	//////////////////////
	// Definiciones...
	public:

	enum class t_vector {V_X=0, V_Y=1};

	///////////////////////
	// Interface pública.
	public:

	Movil();
	virtual ~Movil();

	const DLibH::Vector_2d& 		acc_vector() const {return vector;}
	DLibH::Vector_2d 			acc_vector() {return vector;}

	float 					acc_vector_x() {return vector.x;}
	float 					acc_vector_y() {return vector.y;}

	void 					accion_gravedad(float delta, float valor_gravedad);

	///////////////////////
	//A implementar.
	virtual float 				obtener_peso() const=0;
	virtual float 				obtener_max_velocidad_caida() const=0;

	///////////////////////
	// Para clases derivadas...
	//TODO: Quizás ganaríamos algo si fueran públic...
	protected:

	//delta: tiempo que ha pasado, vector: referencia a la parte del vector, factor: cantidad de fuerza a aplicar al vector.
	float 					integrar_vector(float delta, float& vector, float factor);
	void 					sumar_vector(float, t_vector);
	void 					establecer_vector(float, t_vector);
	void 					establecer_vector(const DLibH::Vector_2d v) {vector=v;}
	float& 					ref_vector_x() {return vector.x;}
	float& 					ref_vector_y() {return vector.y;}

	//////////////////////
	// Propiedades...
	private:

	DLibH::Vector_2d 			vector;

};

}
#endif
