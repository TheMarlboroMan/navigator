#ifndef AUDIO_REPRODUCIR_H
#define AUDIO_REPRODUCIR_H

#include "../../framework/derivada/audio.h"


/**
* Estructura de control de audio que indica audio que puede reproducirse o
* que está en reproduccion.
*/

namespace App_Audio
{

class Audio_reproducir
{
	//////////////////////
	//Interface pública.
	public:

	enum class tipos_reproduccion {simple, repetido};

						Audio_reproducir(tipos_reproduccion, int id_snd, int vol, int ppan);
						~Audio_reproducir();

	void 					turno(float p_delta);
	void					detener_sonido();
	int					acc_id() const {return id;}
	tipos_reproduccion 			acc_tipo_reproduccion() const {return tipo_reproduccion;}
	int 					acc_id_sonido() const {return id_sonido;}
	int 					acc_volumen() const {return volumen;}
	int 					acc_pan() const {return pan;}
	bool					es_finalizado() const;
	bool					es_expirado() const;

	//////////////////////
	//Privado.
	private:

	static int				id_siguiente;

	void 					liberar_canal();
	void 					iniciar_reproduccion();

	DLibA::Canal_audio 			canal;
	int 					id;
	tipos_reproduccion 			tipo_reproduccion;
	int	 				id_sonido;
	int 					volumen;
	int 					pan;
	bool 					iniciada_reproduccion;

};

}

#endif
