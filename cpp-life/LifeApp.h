#ifndef LIFE_APP_H
#define LIFE_APP_H

#include <SDL2/SDL.h>
#include "LifeModel.h"
#include "Constants.h"

class LifeApp
{
	public:
		LifeApp()
		{
			window = NULL;
			renderer = NULL;
			running = true;
			pause = false;
			cellSetupMode = false;
			cellEraseMode = false;
			lifeModel = new LifeModel(SCREEN_WIDTH / CELL_SIZE, SCREEN_HEIGHT / CELL_SIZE);
		}

		~LifeApp()
		{
			    delete lifeModel;
		}

		int execute();

	private:
		bool running;
		SDL_Window* window;
		SDL_Renderer* renderer;
		LifeModel* lifeModel;
		bool pause;
		bool cellSetupMode;
		bool cellEraseMode;

		bool init();
		void onEvent(SDL_Event*);
		void cleanup();
		void drawGrid();
		void drawHorizontalLines();
		void drawVerticalLines();
		void fillCells();
};

#endif
