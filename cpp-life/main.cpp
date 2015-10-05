#include <iostream>
#include <SDL2/SDL.h>
#include "LifeModel.h"

using std::cerr;
using std::endl;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Surface* surface = NULL;

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cerr << "SDL could not be initialized: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		window = SDL_CreateWindow("Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			cerr << "Window could not be created: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			surface = SDL_GetWindowSurface(window);
			SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
		}
	}
	return success;
}

void close()
{
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}

int main(int argc, char** argv)
{
	if (init())
	{
		bool quit = false;
		SDL_Event event;

		while (!quit)
		{
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}
			}
			SDL_UpdateWindowSurface(window);
		}
	}
	close();
	return 0;
}
