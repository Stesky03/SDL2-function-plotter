#include "engine.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

Game* game = 0;
int main(int argc, char* argv[])
{
	Uint32 frameStart, frameTime;
	game = new Game();
	game->init("Engine", 100, 100, 1280, 720, 0);
	while (game->running())
	{
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
		{
			SDL_Delay((int)(DELAY_TIME - frameTime));
		}
	}
	game->clean();
	return 0;
}