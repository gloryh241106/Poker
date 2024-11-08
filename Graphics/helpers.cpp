#include "helpers.h"

namespace Pos
{
	SDL_Rect playerHandPos[5] = {
		{0, 0, 88, 124},
		{88, 0, 88, 124},
		{88 * 2, 0, 88, 124},
		{88 * 3, 0, 88, 124},
		{88 * 4, 0, 88, 124}};
}

namespace Helper
{
	bool coordInRect(int x, int y, SDL_Rect rect)
	{
		return (rect.x <= x && rect.x + rect.w >= x && rect.y <= y && rect.y + rect.h >= y);
	}
}