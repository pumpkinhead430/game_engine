#include "pch.h"
#include "VisableObj.h"
VisableObj::VisableObj(SDL_Renderer *renderer, vector<string>* curr_ani_start, string path, int x, int y, int damage, int id)
{
	this->image_info->x = x;
	this->image_info->y = y;
	this->curr_ani_start = curr_ani_start;
	this->current_image = new Image(path, renderer);
	this->image_info->h = current_image->height;
	this->image_info->w = current_image->width;
	this->current_damage = damage;
	this->id = id;
}

VisableObj::VisableObj(SDL_Renderer* renderer, int x, int y, int id)
{
	this->current_image = nullptr;
	this->image_info->x = x;
	this->image_info->y = y;
	this->id = id;
}


bool VisableObj::In(SDL_Rect* place)
{
	if (SDL_HasIntersection(place, image_info))
		return true;
	return false;
}



vector<string>* VisableObj::GetAniStarters(){ return this->curr_ani_start; }
Image * VisableObj::GetCurrentImage() { return this->current_image; }
int VisableObj::GetId() { return this->id; }
string VisableObj::GetType(){ return "VisableObj"; }
int VisableObj::GetDamage() { return this->current_damage; }
void VisableObj::SetDamage(int damage) { this->current_damage = damage; }
SDL_Rect* VisableObj::GetInfo() { return this->image_info; }
void VisableObj::SetXPos(int pos) { this->image_info->x = pos; }
void VisableObj::SetYPos(int pos) { this->image_info->y = pos; }
VisableObj::~VisableObj()
{
}
