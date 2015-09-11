#ifndef DEFINICIONES_ANIMACIONES_H
#define DEFINICIONES_ANIMACIONES_H

namespace App_Definiciones
{

enum animaciones
{
	sprites, 
	particulas
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
	salida
};

enum animaciones_particulas
{
	humo=1,
	explosion,
	chatarra
};


}

#endif
