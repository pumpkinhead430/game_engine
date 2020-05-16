#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Image.h"
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
	Image* endImage;

public:
	Win(SDL_Renderer* renderer, int startX, int endX, int startY, int endY, string action, int id, string type, int characterId, string endImagePath);
	bool MetConditon(vector<Movable*>* all_objects);
	Movable* GetCharacter(vector<Movable*>* movableObjects);
	Image* GetImage();

};

