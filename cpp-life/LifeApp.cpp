#include <iostream>
#include "LifeApp.h"

using std::cerr;
using std::endl;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int CELL_SIZE = 10;

const Uint8 BLACK_R = 0x00;
const Uint8 BLACK_G = 0x00;
const Uint8 BLACK_B = 0x00;

const Uint8 WHITE_R = 0xFF;
const Uint8 WHITE_G = 0xFF;
const Uint8 WHITE_B = 0xFF;

const Uint8 OPAQUE = 0xFF;

LifeApp::LifeApp()
{
	window = NULL;
	renderer = NULL;
	running = true;
	lifeModel = new LifeModel(SCREEN_WIDTH, SCREEN_HEIGHT);
}

LifeApp::~LifeApp()
{
	delete lifeModel;
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
		SDL_SetRenderDrawColor(renderer, WHITE_R, WHITE_G, WHITE_B, OPAQUE);
		SDL_RenderClear(renderer);
		drawGrid();
		onLoop();
		fillCells();
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
				SDL_SetRenderDrawColor(renderer, WHITE_R, WHITE_G, WHITE_B, OPAQUE);
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
	SDL_SetRenderDrawColor(renderer, BLACK_R, BLACK_G, BLACK_B, OPAQUE);
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

void LifeApp::fillCells()
{
	for (int i = 0; i < SCREEN_WIDTH; i += CELL_SIZE)
	{
		int row = i / CELL_SIZE;

		for (int j = 0; j < SCREEN_HEIGHT; j += CELL_SIZE)
		{
			int col = j / CELL_SIZE;

			if (lifeModel->getCell(row, col))
			{
				SDL_Rect cell = {i, j, CELL_SIZE, CELL_SIZE};
				SDL_SetRenderDrawColor(renderer, BLACK_R, BLACK_G, BLACK_B, OPAQUE);
				SDL_RenderFillRect(renderer, &cell);
			}
		}
	}
}
