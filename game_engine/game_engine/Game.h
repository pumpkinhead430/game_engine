#pragma once
#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "VisableObj.h"
#include "Movable.h"
#include "InputHandler.h"
using namespace std;
class Game
{
public:
	Game();
	~Game();
	void init(const char* title, int width, int height, bool fullscreen);
	void handleEvents(vector<Movable*> *movobj);
	void update(vector<Movable*> *movobjs);
	bool running();
	void render(vector<VisableObj*>* Torender);
	void clean();
	SDL_Renderer *GetRenderer();

private:
	bool isRunning = false;
	InputHandler KeyInput;
	SDL_Window *window;
	SDL_Renderer *renderer;
};

