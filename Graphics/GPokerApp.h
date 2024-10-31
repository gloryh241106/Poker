#ifndef __G_POKER_APP__
#define __G_POKER_APP__

#include "libs.h"
#include "GCard.h"

class GPokerApp
{
private:
	SDL_Window *m_window;
	SDL_Surface *m_window_surface;
	SDL_Renderer *m_window_renderer;
	SDL_Event m_window_event;

	SDL_Rect card_pos;
	int dx = 1, dy = 1;
	SDL_Rect card_view;
	GCard card[10];

	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;

public:
	GPokerApp(/* args */);
	~GPokerApp();
	void update();
	void draw();
};

#endif