#ifndef __G_POKER_HELPERS__
#define __G_POKER_HELPERS__

#include "libs.h"

namespace Pos
{
	extern SDL_Rect playerHandPos[5];
}

namespace Helper
{
	extern bool coordInRect(int x, int y, SDL_Rect rect);
}

#endif