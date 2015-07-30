#include "contador_tiempo.h"
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace App_Juego_Sistemas;

void Contador_tiempo::turno(float delta)
{
	tiempo_restante-=delta;
	if(tiempo_restante < 0.0) tiempo_restante=0.0;
}

std::string Contador_tiempo::formatear_tiempo_restante()
{
	int minutos=tiempo_restante / 60.0;
	float fsegundos=fmod(tiempo_restante, 60.0);
	int segundos=fsegundos;

	double dummy=0.0;
	double tdecimas=modf(fsegundos, &dummy);
	int decimas=tdecimas*1000;

	std::stringstream ss;
	ss.fill('0');
	ss.width(2);

	ss<<minutos<<":"<<segundos<<":";
	ss.width(3);
	ss<<decimas;

	return ss.str();
}
