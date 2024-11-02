#include "GCard.h"

GCard::~GCard()
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
	}
}