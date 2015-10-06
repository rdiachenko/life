#ifndef LIFE_APP_H
#define LIFE_APP_H

#include <SDL2/SDL.h>

class LifeApp
{
	public:
		LifeApp();
		int onExecute();

	private:
		bool running;
		SDL_Window* window;
		SDL_Renderer* renderer;
		bool onInit();
		void onEvent(SDL_Event*);
		void onLoop();
		void onCleanup();
		void drawGrid();
		void drawHorizontalLines();
		void drawVerticalLines();
};

#endif
