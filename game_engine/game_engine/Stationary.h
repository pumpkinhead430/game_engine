#pragma once
#include "VisableObj.h"
class Stationary :public VisableObj
{
public:
	Stationary(int damage, SDL_Renderer* renderer, string path, int x, int y);
	~Stationary();
private:
	int damage;
};


