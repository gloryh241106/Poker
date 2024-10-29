
#include "PokerApp.h"

PokerApp::PokerApp()
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

	// // Create main surface
	// m_window_surface = SDL_GetWindowSurface(m_window);

	// if (!m_window_surface)
	// {
	// 	std::cout << "Failed to get window's surface\n";
	// 	std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
	// 	return;
	// }

	// Create renderer
	m_window_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

	if (!m_window_renderer)
	{
		std::cout << "Failed to get window's renderer\n";
		std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
		return;
	}

	card_surface = IMG_Load("Assets/Cards/2s.png");
	if (!card_surface)
	{
		std::cout << "Failed to create card_suface\n";
		return;
	}
	card_texture = SDL_CreateTextureFromSurface(m_window_renderer, card_surface);
	if (!card_texture)
	{
		std::cout << "Failed to create card_texture\n";
		return;
	}
	SDL_FreeSurface(card_surface);

	// Define card rects
	card_pos.h = 124; // 124;
	card_pos.w = 88;  // 88;
	card_pos.x = 0;
	card_pos.y = 0;
	card_view.h = 124; // 124;
	card_view.w = 88;  // 88;
	card_view.x = 0;
	card_view.y = 0;
}

PokerApp::~PokerApp()
{
	SDL_DestroyTexture(card_texture);
	SDL_DestroyRenderer(m_window_renderer);
	SDL_DestroyWindow(m_window);
	IMG_Quit();
	SDL_Quit();
}

void PokerApp::update()
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
			}
		}

		draw();
	}
}

void PokerApp::draw()
{
	card_pos.x += dx;
	card_pos.y += dy;
	if (card_pos.x == 0 || card_pos.x + card_pos.w == WINDOW_WIDTH)
		dx = -dx;
	if (card_pos.y == 0 || card_pos.y + card_pos.h == WINDOW_HEIGHT)
		dy = -dy;

	// Draw to the back buffer
	SDL_SetRenderDrawColor(m_window_renderer, 0x04, 0x80, 0x40, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(m_window_renderer);
	SDL_SetRenderDrawColor(m_window_renderer, 0xff, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(m_window_renderer, &card_pos);

	// Draw card
	SDL_RenderCopy(m_window_renderer, card_texture, NULL, &card_pos);
	// SDL_RenderFillRect(m_window_renderer, &card_pos);

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