#ifndef LIFE_APP_H
#define LIFE_APP_H

#include <SDL2/SDL.h>
#include "LifeModel.h"

class LifeApp
{
	public:
		LifeApp();
		~LifeApp();
		int onExecute();

	private:
		bool running;
		SDL_Window* window;
		SDL_Renderer* renderer;
		LifeModel* lifeModel;
		bool onInit();
		void onEvent(SDL_Event*);
		void onLoop();
		void onCleanup();
		void drawGrid();
		void drawHorizontalLines();
		void drawVerticalLines();
		void fillCells();
};

#endif
