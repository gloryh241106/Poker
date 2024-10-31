
#include "GPokerApp.h"
#include "GCard.h"

GPokerApp::GPokerApp()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to init SDL\n";
		std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
		return;
	}

	// Create window
	m_window = SDL_CreateWindow("SDL2 Window",
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								WINDOW_WIDTH, WINDOW_HEIGHT,
								0);

	if (!m_window)
	{
		std::cout << "Failed to create window\n";
		std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
		return;
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		std::cout << "Failed to init SDL_image\n";
		std::cout << "SDL_image Error: " << IMG_GetError() << "\n";
		return;
	}

	// Create renderer
	m_window_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

	if (!m_window_renderer)
	{
		std::cout << "Failed to get window's renderer\n";
		std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
		return;
	}

	for (int i = 0; i < 10; i++)
	{
		card[i].texture = IMG_LoadTexture(m_window_renderer, "Assets/Cards/3s.png");
		card[i].dx = i % 2 + 1;
		card[i].dy = i % 3 + 1;
	}
}

GPokerApp::~GPokerApp()
{
	// card.~GCard();
	SDL_DestroyRenderer(m_window_renderer);
	SDL_DestroyWindow(m_window);
	IMG_Quit();
	SDL_Quit();
}

bool coordInRect(int x, int y, SDL_Rect rect)
{
	return (rect.x <= x && rect.x + rect.w >= x && rect.y <= y && rect.y + rect.h >= y);
}

void GPokerApp::update()
{
	bool keep_window_open = true;
	while (keep_window_open)
	{
		while (SDL_PollEvent(&m_window_event) > 0)
		{
			switch (m_window_event.type)
			{
			case SDL_QUIT:
				keep_window_open = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (m_window_event.button.button == SDL_BUTTON_LEFT)
				{
					for (int i = 0; i < 10; i++)
					{
						int mouseX = 0, mouseY = 0;
						SDL_GetMouseState(&mouseX, &mouseY);
						if (coordInRect(mouseX, mouseY, card[i].dstRect))
						{
							card[i].texture = IMG_LoadTexture(m_window_renderer, "Assets/Cards/2d.png");
							card[i].dx = -card[i].dx;
							card[i].dy = -card[i].dy;
							break;
						}
					}
				}
			}
		}

		draw();
	}
}

void GPokerApp::draw()
{
	// Draw background
	SDL_SetRenderDrawColor(m_window_renderer, 0x04, 0x80, 0x40, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(m_window_renderer);

	// Draw card
	// card.draw();
	for (int i = 0; i < 10; i++)
	{
		card[i].dstRect.x += card[i].dx;
		card[i].dstRect.y += card[i].dy;
		if (card[i].dstRect.x == 0 || card[i].dstRect.x + card[i].CARD_WIDTH >= WINDOW_WIDTH)
			card[i].dx = -card[i].dx;
		if (card[i].dstRect.y == 0 || card[i].dstRect.y + card[i].CARD_HEIGHT >= WINDOW_HEIGHT)
			card[i].dy = -card[i].dy;
		SDL_RenderCopy(m_window_renderer, card[i].texture, NULL, &card[i].dstRect);
	}
	// Display image on the screen
	SDL_RenderPresent(m_window_renderer);
}

SDL_Surface *load_surface(char const *path)
{
	SDL_Surface *image_surface = SDL_LoadBMP(path);

	if (!image_surface)
		return 0;

	return image_surface;
}