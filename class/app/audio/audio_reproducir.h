#ifndef AUDIO_REPRODUCIR_H
#define AUDIO_REPRODUCIR_H

#include "../../framework/derivada/audio.h"


/**
* Estructura de control de audio que indica audio que puede reproducirse o
* que está en reproduccion.
*/

namespace App_Audio
{

struct Info_audio_reproducir
{
	private:
	static int				id_siguiente;

	public:

	enum class tipos_reproduccion {simple, repetido};

						Info_audio_reproducir(tipos_reproduccion, int id_snd, int vol, int ppan);


	int 					id;
	tipos_reproduccion 			tipo_reproduccion;
	int	 				id_sonido;
	int 					volumen;
	int 					pan;
};

class Audio_reproducir
{
	//////////////////////
	//Interface pública.
	public:

	enum class estados {sin_iniciar, reproduciendo, finalizado, desvinculado};

						Audio_reproducir(const Info_audio_reproducir&);
//TODO: Debe ser copiable, simplemente. Si no, es mierda.
//						Audio_reproducir(const Audio_reproducir& a);
						~Audio_reproducir();

	void 					turno(float p_delta);
	void					detener_sonido();
	int					acc_id() const {return info.id;}
	bool					es_finalizado() const {return estado==estados::finalizado;}
	bool					es_desvinculado() const {return estado==estados::desvinculado;}

	//////////////////////
	//Privado.
	private:

	void 					iniciar_reproduccion();
	DLibA::Canal_audio 			canal;
	Info_audio_reproducir			info;
	estados 				estado;

};

}

#endif
