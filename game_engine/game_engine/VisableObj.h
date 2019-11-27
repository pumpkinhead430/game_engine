#pragma once
#include <iostream>
#include <vector>
#include<array>
#include <list>
#include "SDL.h"
#include "Image.h"
#include "SDL_image.h"
using namespace std;
static int ID = 0;
class VisableObj
{


protected:
	SDL_Rect *image_info = new SDL_Rect();
	int id;
	Image *current_image;

public:
	VisableObj(SDL_Renderer *renderer, string path, int x, int y);
	VisableObj(SDL_Renderer* renderer, int x, int y);
	void SetXPos(int pos);
	void SetYPos(int pos);
	int GetId();
	Image *GetCurrentImage();
	SDL_Rect *GetInfo();
	~VisableObj();
};

