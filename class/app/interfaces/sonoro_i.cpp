#include "sonoro_i.h"

using namespace App_Interfaces;

int Sonoro_I::insertar_reproducir(const App_Audio::Info_audio_reproducir& a) 
{
	reproducir.push_back(a);
	return a.id;
}
