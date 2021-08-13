#include "Game.h"

int main(int, char**)
{
	Game game;
	game.Initialize();

	bool quit = false;
	SDL_Event event;

	while (!quit && !game.IsQuit())
	{
		SDL_PollEvent(&event);

		switch (event.window.event)
		{
		case SDL_WINDOWEVENT_CLOSE:
			quit = true;
			break;
		}

		game.Update();
		game.Draw();
	}
	
	SDL_Quit();
	return 0;
}

