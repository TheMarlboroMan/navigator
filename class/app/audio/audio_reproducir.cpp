#include "audio_reproducir.h"

using namespace App_Audio;
using namespace DLibA;

int Audio_reproducir::id_siguiente=1;

Audio_reproducir::Audio_reproducir(tipos_reproduccion tr, int id_snd, int vol, int ppan)
	:id(id_siguiente), tipo_reproduccion(tr),
	id_sonido(id_snd),
	volumen(vol),
	pan(ppan)
{
	++id_siguiente;
}

Audio_reproducir::~Audio_reproducir()
{
	liberar_canal();
}

void Audio_reproducir::detener_sonido()
{
	canal.forzar_parada();
}

bool Audio_reproducir::es_finalizado() const
{
	return canal.es_vinculado() && !canal.es_reproduciendo();
}

/**
* Técnicamente lo que hace es darnos el estado que se queda tras liberar eñ
* el canal, que es el mismo que tendría al iniciarse.
*/

bool Audio_reproducir::es_expirado() const
{
	return !canal.es_vinculado() && !iniciada_reproduccion;
}

void Audio_reproducir::turno(float p_delta)
{
	//TODO TODO TODO: Subclasear.

	switch(tipo_reproduccion)
	{
		case tipos_reproduccion::simple:
		case tipos_reproduccion::repetido:
			if(!iniciada_reproduccion)
			{
				iniciar_reproduccion();
			}
			else if(es_finalizado())
			{
				liberar_canal();
			}
		break;
	}
}

void Audio_reproducir::liberar_canal()
{
	if(canal.es_vinculado())
	{
		canal.desactivar_monitoreado();
		canal.forzar_parada();
		canal.desvincular();
	}

	iniciada_reproduccion=false;
}

void Audio_reproducir::iniciar_reproduccion()
{
	if(!canal.es_vinculado()) 
	{
		try
		{
			canal=Audio::obtener_canal_libre();
			canal.activar_monitoreado();
		}
		catch(const Excepcion_audio& e)
		{
			LOG<<e.mensaje<<std::endl;
			return;
		}
		catch(const DLibA::Excepcion_controlador_audio& e)
		{
			LOG<<"WARNING: Imposible obtener canal de audio para Audio_reproducir."<<std::endl;
			return;
		}
	}

	int repeticiones=0;

	//TODO: Subclass this bitch.
	switch(tipo_reproduccion)
	{
		case tipos_reproduccion::simple:	repeticiones=0; break;
		case tipos_reproduccion::repetido: 	repeticiones=-1; break;
	}
	
	int pan_d=(pan / 2);		
	int pan_i=255-pan_d;

	canal.iniciar_reproduccion(
		DLibA::Estructura_sonido(
				DLibA::Gestor_recursos_audio::obtener_sonido(id_sonido), 
			volumen, repeticiones, pan_i, pan_d));

	iniciada_reproduccion=true;
}
