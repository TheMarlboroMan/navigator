#ifndef SONORO_I_H
#define SONORO_I_H

#include <vector>
#include "../audio/audio_reproducir.h"
#include "../audio/audio_detener.h"

namespace App_Interfaces
{
class Sonoro_I
{
	///////////////////
	//Interface pública.
	public:

	virtual bool					es_sonoro_borrar() const=0;

	bool						hay_reproducir() const {return reproducir.size();}
	bool						hay_detener() const {return detener.size();}
	void						insertar_reproducir(const App_Audio::Info_audio_reproducir& a) {reproducir.push_back(a);}
	void						insertar_detener(const App_Audio::Audio_detener& a) {detener.push_back(a);}
	void						reset_reproducir() {reproducir.clear();}
	void						reset_detener() {detener.clear();}

	std::vector<App_Audio::Info_audio_reproducir>&	acc_reproducir() {return reproducir;}
	std::vector<App_Audio::Audio_detener>&		acc_detener() {return detener;}

	///////////////////
	//Interface privada:
	private:

	std::vector<App_Audio::Info_audio_reproducir>	reproducir;
	std::vector<App_Audio::Audio_detener>		detener;
};
}

#endif
