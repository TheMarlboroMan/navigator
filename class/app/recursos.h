#ifndef RECURSOS_PROYECTO_H
#define RECURSOS_PROYECTO_H

namespace App
{

class Recursos_graficos
{
	private:

	Recursos_graficos();

	public:

	enum superficies{
		RS_FUENTE_BASE=1
	};

	enum texturas{
		RT_DEFECTO=1,
		RT_AUTOMAPA=2,
		RT_TEMPLATE_TILES=3
	};
};

class Recursos_audio
{
	private:

	Recursos_audio();

	public:

	enum musicas{
		RM_BLIND_SHIFT=1
	};

	enum sonidos{
		RS_DEFECTO=1,
		rs_disparo=10,
		rs_explosion=11,
		rs_golpe=12,
		rs_golpe_jugador=13,
		rs_recargar_escudo=14,
		rs_estasis=15
	};
};

}
#endif
