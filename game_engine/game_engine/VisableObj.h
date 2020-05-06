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
	int id = -1;
	int current_damage = 0;
	vector<string> *curr_ani_start = new vector<string>(0);
	Image *current_image;

public:
	VisableObj(SDL_Renderer *renderer, vector<string>* curr_ani_start, string path, int x, int y, int damage, int id);
	VisableObj(SDL_Renderer* renderer, int x, int y, int id);
	void SetXPos(int pos);
	void SetYPos(int pos);
	int GetId();
	virtual string GetType();
	int GetDamage();
	void SetDamage(int damage);
	bool In(SDL_Rect* place);
	vector<string>* GetAniStarters();
	Image *GetCurrentImage();
	SDL_Rect *GetInfo();
	~VisableObj();
};

