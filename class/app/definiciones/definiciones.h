#ifndef DEFINICIONES_H
#define DEFINICIONES_H

/**
* Definiciones de varios tipos compartidos a lo largo de la aplicación.
*/

namespace App_Definiciones
{

struct tipos
{	
	private:
	tipos();

	public:
	typedef unsigned int t_dim;
	static const t_dim DIM_CELDA=32;	

	struct coordenadas_t_dim
	{
		t_dim x, y;
		coordenadas_t_dim(t_dim px, t_dim py)
			:x(px), y(py)
		{}

		bool operator<(const coordenadas_t_dim& otro) const
		{
			if(y > otro.y) return false;
			else if(y < otro.y) return true;
			else return x < otro.x;
		}

		bool operator==(const coordenadas_t_dim& otro) const
		{
			return x==otro.x && y==otro.y;
		}
	};
};

enum class direcciones {nada=0, arriba=1, derecha=2, abajo=4, izquierda=8};

direcciones convertir_en_direccion(int); /**@throw std::runtime_error */

direcciones obtener_direccion_contraria(direcciones s);
/*constexpr*/ direcciones operator|(direcciones a, direcciones b);
/*constexpr*/ direcciones operator&(direcciones a, direcciones b);
}
#endif
