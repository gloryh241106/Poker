#ifndef __G_CARD__
#define __G_CARD__

#include "libs.h"

struct GCard
{
	static const int CARD_WIDTH = 88;
	static const int CARD_HEIGHT = 124;
	SDL_Rect dstRect = {0, 0, CARD_WIDTH, CARD_HEIGHT};
	SDL_Texture *texture;
	SDL_Renderer *windowRenderer;
	int dx = 0, dy = 0;
	~GCard();
};

#endif