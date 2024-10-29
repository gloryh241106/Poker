#ifndef __POKER_APP__
#define __POKER_APP__

// Using SDL and standard IO
// https://stackoverflow.com/questions/5919996/how-to-detect-reliably-mac-os-x-ios-linux-windows-in-c-preprocessor
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <SDL.h>
#elif __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#else
#error "Operating system not supported!"
#endif

#include <iostream>
#include <string>

class PokerApp
{
private:
	SDL_Window *m_window;
	SDL_Surface *m_window_surface;
	SDL_Renderer *m_window_renderer;
	SDL_Event m_window_event;

	SDL_Surface *card_surface;
	SDL_Rect card_pos;
	int dx = 1, dy = 1;
	SDL_Rect card_view;
	SDL_Texture *card_texture;

	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;

public:
	PokerApp(/* args */);
	~PokerApp();
	void update();
	void draw();
};

#endif