#include "gestor_audio.h"
#include <algorithm>

using namespace App_Audio;

void Gestor_audio::insertar(const Info_audio_reproducir& a)
{
	reproducir.push_back(Audio_reproducir(a));
}

void Gestor_audio::insertar(const Audio_detener& a)
{
	detener.push_back(a);
}

void Gestor_audio::turno(float delta)
{
//	Audio::debug_estado_canales();

	//Controlar las solicitudes de detener sonido.
	for(auto& d : detener)
	{
		int idd=d.acc_id_destino();
		auto it=std::find_if(std::begin(reproducir), std::end(reproducir),
			[idd](Audio_reproducir& a) {return a.acc_id()==idd;});

		if(it !=  std::end(reproducir))
		{
			it->detener_sonido();
		}
	}

	detener.clear();

	//Procesar los que estén en marcha.
	auto	it=std::begin(reproducir);
	while(it < std::end(reproducir))
	{
		it->turno(delta);
		if(it->es_finalizado())
		{
			it=reproducir.erase(it);
		}
		else 
		{
			++it;
		}
	}
}
