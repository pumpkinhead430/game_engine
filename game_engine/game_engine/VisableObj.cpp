#include "pch.h"
#include "VisableObj.h"
VisableObj::VisableObj(SDL_Renderer *renderer, string path, int x, int y)
{
	this->image_info->x = x;
	this->image_info->y = y;
	this->current_image = new Image(path, renderer);
	this->image_info->h = current_image->height;
	this->image_info->w = current_image->width;
	this->id = ID;
	ID++;
}

VisableObj::VisableObj(SDL_Renderer* renderer, int x, int y)
{
	this->current_image = nullptr;
	this->image_info->x = x;
	this->image_info->y = y;
	this->id = ID;
	ID++;
}

Image * VisableObj::GetCurrentImage() { return this->current_image; }
int VisableObj::GetId() { return this->id; }
SDL_Rect* VisableObj::GetInfo() { return this->image_info; }
void VisableObj::SetXPos(int pos) { this->image_info->x = pos; }
void VisableObj::SetYPos(int pos) { this->image_info->y = pos; }
VisableObj::~VisableObj()
{
}
