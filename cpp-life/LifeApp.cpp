#include <iostream>
#include "LifeApp.h"

using std::cerr;
using std::endl;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int CELL_SIZE = 10;

LifeApp::LifeApp()
{
	window = NULL;
	renderer = NULL;
	running = true;
}

int LifeApp::onExecute()
{
	if (!onInit())
	{
		cerr << "Failed to initialize" << endl;
		return -1;
	}
	SDL_Event event;

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			onEvent(&event);
		}
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		drawGrid();
		onLoop();
		SDL_RenderPresent(renderer);
	}
	onCleanup();
	return 0;
}

bool LifeApp::onInit()
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
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (renderer == NULL)
			{
				cerr << "Renderer could not be created: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}
	return success;
}

void LifeApp::onEvent(SDL_Event* event)
{
	if (event->type == SDL_QUIT)
	{
		running = false;
	}
}

void LifeApp::onLoop()
{

}

void LifeApp::onCleanup()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	SDL_Quit();
}

void LifeApp::drawGrid()
{
	SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
	drawHorizontalLines();
	drawVerticalLines();
}

void LifeApp::drawHorizontalLines()
{
	for (int i = CELL_SIZE; i < SCREEN_HEIGHT; i += CELL_SIZE)
	{
		SDL_RenderDrawLine(renderer, 0, i, SCREEN_WIDTH, i);
	}
}

void LifeApp::drawVerticalLines()
{
	for (int i = CELL_SIZE; i < SCREEN_WIDTH; i += CELL_SIZE)
	{
		SDL_RenderDrawLine(renderer, i, 0, i, SCREEN_HEIGHT);
	}
}
