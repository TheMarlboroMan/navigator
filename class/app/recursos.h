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
		rs_fuente_base=1
	};

	enum texturas{
		rt_defecto=1,
		rt_automapa=2,
		rt_template_tiles=3,
		rt_particulas=4
	};
};

class Recursos_audio
{
	private:

	Recursos_audio();

	public:

	enum musicas{
		rm_blind_shift=1
	};

	enum sonidos{
		RS_DEFECTO=1,
		rs_explosion=11,
		rs_disparo=10,
		rs_golpe=12,
		rs_golpe_jugador=13,
		rs_recargar_escudo=14,
		rs_estasis=15,
		rs_recoger_bonus=16,
		rs_disparo_pared=17
	};
};

}
#endif
