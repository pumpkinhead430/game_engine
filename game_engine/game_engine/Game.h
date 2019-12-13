#pragma once
#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "VisableObj.h"
#include "Stationary.h"
#include "Movable.h"
//#include "CollisionFunctions.h"
#include "InputHandler.h"
using namespace std;
class Game
{
public:
	Game();
	~Game();
	void init(const char* title, int width, int height, bool fullscreen, int gravity);
	VisableObj* Pixel_Colide(Movable* character, int i, int j, vector<VisableObj*>* all_objects, int dst_x, int dst_y);
	void who_colided(Movable* character, vector<VisableObj*>* all_objects, vector<VisableObj*>* colided, int dst_x, int dst_y);
	void ActivateAffect(VisableObj* collision_object, Movable* colided_object);
	void Damage(VisableObj* collision_object, Movable* colided_object);
	void collision(vector<VisableObj*>* all_objects, vector<Movable*>* movablechars, vector<VisableObj*>* colided);
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

