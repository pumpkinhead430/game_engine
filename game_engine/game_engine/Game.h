#pragma once
#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "VisableObj.h"
#include "Stationary.h"
#include "Movable.h"
#include "InputHandler.h"
using namespace std;
class Game
{
public:
	Game();
	~Game();
	void init(const char* title, int width, int height, bool fullscreen, int gravity);
	void handleEvents(vector<Movable*> *movobj);
	bool running();
	void render(vector<Movable*>* Torender, vector<VisableObj*>* stationary);
	void clean();
	SDL_Renderer *GetRenderer();

private:
	int gravity;
	bool isRunning = false;
	InputHandler KeyInput;
	SDL_Window *window;
	SDL_Renderer *renderer;
};

