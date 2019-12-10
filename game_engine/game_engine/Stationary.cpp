#include "pch.h"
#include "Stationary.h"


Stationary::Stationary(int damage, SDL_Renderer* renderer, vector<string>* curr_ani_start, string path, int x, int y):
	VisableObj(renderer, curr_ani_start, path, x, y)
{
	this->damage = damage;
}


Stationary::~Stationary()
{
}
