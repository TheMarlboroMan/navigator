#ifndef DEFINICIONES_ANIMACIONES_H
#define DEFINICIONES_ANIMACIONES_H

namespace App_Definiciones
{

enum animaciones
{
	sprites, 
	particulas,
	celdas_template
};

enum animaciones_sprites
{
	jugador=1,
	bonus_tiempo,
	bonus_salud,
	proyectil_rojo,
	proyectil_azul,
	enemigo_basico,
	enemigo_rebote,
	salida,
	obstaculo_generico
};

enum animaciones_particulas
{
	humo=1,
	explosion,
	chatarra
};

enum definiciones_particulas
{
	min_chatarra=9,
	max_chatarra=40,
	lon_humo=4,
	lon_explosion=4
};

}

#endif
