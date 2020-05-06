#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <vector>
#include "VisableObj.h"
#include "Movable.h"
using namespace std;
class Win
{
private:
	SDL_Rect* place = new SDL_Rect();
	string action;
	int id;
	int characterId;
	string type;

public:
	Win(int startX, int endX, int startY, int endY, string action, int id, string type, int characterId);
	bool MetConditon(vector<Movable*>* all_objects);
	Movable* GetCharacter(vector<Movable*>* movableObjects);

};

