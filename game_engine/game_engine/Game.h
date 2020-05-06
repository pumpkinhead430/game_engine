#pragma once
#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "Image.h"
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/istreamwrapper.h>
#include <fstream>
#include "VisableObj.h"
#include "animation.h"
#include "Movable.h"
#include "Win.h"
//#include "CollisionFunctions.h"
#include "InputHandler.h"
using namespace std;
using namespace rapidjson;
class Game
{
public:
	Game(const char* title, int width, int height, bool fullscreen, string background_path, int gravity);
	~Game();
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
	void checkEnd();
	SDL_Renderer* GetRenderer();

private:
	void SetUp();
	animation* GetAnimationJson(const Value& obj);
	Movable* GetMovableJson(const Value& obj);
	VisableObj* GetStationaryJson(const Value& obj);
	Win* GetWinJson(const Value& obj);
	int gravity;
	Image* background;
	SDL_Rect* background_rect = new SDL_Rect();
	vector<Movable*>* movablechars = new vector<Movable*>(0);//all Movable objects
	vector<VisableObj*>* stationaryobjs = new vector<VisableObj*>(0);//all Stationary objects
	vector<Win*>* winObjs = new vector<Win*>(0);//all Win objects
	vector<Win*>* lossObjs = new vector<Win*>(0);//all Loss objects
	vector<VisableObj*>* all_objects = new vector<VisableObj*>(0);//all visable objects
	vector<VisableObj*>* colided = new vector<VisableObj*>(0);// all colided objects
	vector<Movable*>* dead = new vector<Movable*>(0);
	bool win = false;
	bool loss = false;
	bool isRunning = false;
	InputHandler KeyInput;
	SDL_Window* window;
	SDL_Renderer* renderer;
};