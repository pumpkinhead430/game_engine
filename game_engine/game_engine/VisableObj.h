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
	int current_damage;
	vector<string> *curr_ani_start = new vector<string>(0);
	Image *current_image;

public:
	VisableObj(SDL_Renderer *renderer, vector<string>* curr_ani_start, string path, int x, int y, int damage);
	VisableObj(SDL_Renderer* renderer, int x, int y);
	void SetXPos(int pos);
	void SetYPos(int pos);
	int GetId();
	virtual string GetType();
	int GetDamage();
	void SetDamage(int damage);
	vector<string>* GetAniStarters();
	Image *GetCurrentImage();
	SDL_Rect *GetInfo();
	~VisableObj();
};

