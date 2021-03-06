#include "input.h"

void Input::configurar()
{
	//El input I_ESCAPE es la tecla SDLK_ESCAPE. Simple.
	mapa_teclado.insert(std::make_pair(I_ESCAPE, SDL_SCANCODE_ESCAPE));
	mapa_teclado.insert(std::make_pair(I_ESPACIO, SDL_SCANCODE_SPACE));
	mapa_teclado.insert(std::make_pair(I_IZQUIERDA, SDL_SCANCODE_LEFT));
	mapa_teclado.insert(std::make_pair(I_DERECHA, SDL_SCANCODE_RIGHT));
	mapa_teclado.insert(std::make_pair(I_ARRIBA, SDL_SCANCODE_UP));
	mapa_teclado.insert(std::make_pair(I_ABAJO, SDL_SCANCODE_DOWN));

	mapa_teclado.insert(std::make_pair(I_CAMBIAR_MODO_PANTALLA, SDL_SCANCODE_F));
	mapa_teclado.insert(std::make_pair(I_INTERCAMBIAR_PANTALLA_PAUSA, SDL_SCANCODE_TAB));

	mapa_teclado.insert(std::make_pair(I_USAR_SELECCION, SDL_SCANCODE_LCTRL));
	mapa_teclado.insert(std::make_pair(I_ESTASIS, SDL_SCANCODE_SPACE));
	mapa_teclado.insert(std::make_pair(I_RECARGA_ESCUDO, SDL_SCANCODE_LSHIFT));

	mapa_raton.insert(std::make_pair(I_CLICK_I, SDL_BUTTON_LEFT));
	mapa_raton.insert(std::make_pair(I_CLICK_I, SDL_BUTTON_RIGHT));
}
