#include "obstaculo_generico.h"

using namespace App_Juego_ObjetoJuego;

Obstaculo_generico::Obstaculo_generico(float x, float y, int tipo)
	:Actor(x, y, 1, 1),
	Objeto_juego_I(),
	tipo(tipo)
{
	//TODO: En función del tipo extraer sus propiedades. Posiblemente
	//sea un objeto estático que se inicialice, lea un fichero y contenga
	//las informaciones de tamaño.

	//TODO: Preparar un tema de animaciones.... Cada animación puede apuntar
	//a un id de recorte en una hoja concreta.
}


unsigned short int Obstaculo_generico::obtener_profundidad_ordenacion()const
{
	//TODO: Quizás pueda ser parte de la definición del propio objeto?.
	return 10;
}

void Obstaculo_generico::transformar_bloque(App_Graficos::Bloque_transformacion_representable &b)const
{
	//TODO: Escoger recorte según animación corriente. Copiar código de 
	//The seer: tenemos una clase que lo único que hace es ciclar el
	//tiempo de animaciones.	
}

	/////////////////
	//Internas

	private:

	int					tipo;
