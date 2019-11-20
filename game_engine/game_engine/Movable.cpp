#include "pch.h"
#include "Movable.h"


Movable::Movable(SDL_Renderer* renderer, string path, int x, int y, vector<animation*>* animations) :VisableObj(renderer, path, x, y)
{//setting the trigger which will be in animations in due time and setting defult all speed and force
	this->dstpos->x = this->image_info->x;
	this->dstpos->y = this->image_info->y;
	this->dstpos->h = this->image_info->h;
	this->dstpos->w = this->image_info->w;
	this->animations = animations;
	this->speed[0] = 0;
	this->force[0] = 0;
	this->speed[1] = 0;
	this->force[1] = 0;
}

//--------------------------------------
bool Movable::Triggered(int input)
{//cheking if animtaion is triggered
	if (input == trigger)
		return true;
	return false;
}

void Movable::AddTriggerForce()
{//
	//this->force[0] -= 1;						//this group of functions shall be change to recive information from animations
	this->force[1] -= 1;
}
//----------------------------------------
void Movable::AddSpeed()
{
	this->speed[0] += this->force[0];
	this->speed[1] += this->force[1];
	this->force[0] = 0;
	this->force[1] = 0;
}

void Movable::AddToPostion()
{
	if (this->id == 1)
		this->SetDst(this->dstpos->y + this->speed[0] + 1, this->dstpos->x + this->speed[1] );
	else
		this->SetDst(this->dstpos->y + this->speed[0], this->dstpos->x + this->speed[1]);
}

void Movable::SetSpeed(int ySpeed, int xSpeed)
{
	this->speed[0] = ySpeed;
	this->speed[1] = xSpeed;
}
void Movable::SetDst(int y, int x) 
{
	this->dstpos->x = x;
	this->dstpos->y = y;
}
void Movable::SetForce(int forcey, int forcex)
{
	this->force[0] = forcey;
	this->force[1] = forcex;
}
SDL_Rect* Movable::GetDst() { return this->dstpos; }
int *Movable::GetForce() { return this->force; }
int Movable::GetSpeedX() { return this->speed[1]; }
int Movable::GetSpeedY() { return this->speed[0]; }
Movable::~Movable()
{
}
