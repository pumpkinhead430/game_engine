#pragma once
#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "Image.h"
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
	void init(const char* title, int width, int height, bool fullscreen, string background_path, int gravity);
	VisableObj* Pixel_Colide(Movable* character, int i, int j, vector<VisableObj*>* all_objects, int dst_x, int dst_y);
	void who_colided(Movable* character, vector<VisableObj*>* all_objects, vector<VisableObj*>* colided, int dst_x, int dst_y);
	void ActivateAffect(VisableObj* collision_object, Movable* colided_object);
	void Damage(VisableObj* collision_object, Movable* colided_object);
	void GetDead();
	bool IsDead(VisableObj* object);
	void collision();
	void handleEvents();
	bool running();
	void render();
	void clean();
	SDL_Renderer* GetRenderer();

private:
	void SetUp();
	int gravity;
	Image *background;
	SDL_Rect* background_rect = new SDL_Rect();
	vector<Movable*>* movablechars = new vector<Movable*>(0);//all Movable objects
	vector<VisableObj*>* stationaryobjs = new vector<VisableObj*>(0);//all Stationary objects
	vector<VisableObj*>* all_objects = new vector<VisableObj*>(0);//all visable objects
	vector<VisableObj*>* colided = new vector<VisableObj*>(0);// all colided objects
	vector<Movable*>* dead = new vector<Movable*>(0);
	bool isRunning = false;
	InputHandler KeyInput;
	SDL_Window* window;
	SDL_Renderer* renderer;
};