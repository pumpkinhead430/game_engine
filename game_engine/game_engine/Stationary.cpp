#include "pch.h"
#include "Stationary.h"


Stationary::Stationary(int damage, SDL_Renderer* renderer, string path, int x, int y):VisableObj(renderer, path, x, y)
{
	this->damage = damage;
}


Stationary::~Stationary()
{
}
