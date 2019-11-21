#include "pch.h"
#include "Movable.h"


Movable::Movable(SDL_Renderer* renderer, string path, int x, int y, vector<animation*>* animations) :VisableObj(renderer, path, x, y)
{//setting the trigger which will be in animations in due time and setting defult all speed and force
	this->dstpos->x = this->image_info->x;
	this->dstpos->y = this->image_info->y;
	this->dstpos->h = this->image_info->h;
	this->dstpos->w = this->image_info->w;
	this->animations = animations;
	this->speed->first = 0;
	this->force->first = 0;
	this->speed->second = 0;
	this->force->second = 0;
}

//--------------------------------------
bool Movable::TriggerAnimation(int input)
{//cheking if animtaion is triggered
	for(int i = 0; i < this->animations->size(); i++)
	{
		if (this->animations->at(i)->IsTriggered(input))
		{
			this->ActivateAnimation(this->animations->at(i));
		}
	}
}


void Movable::ActivateAnimation(animation* ani)
{
	if (this->currani == this->animations->at(0))
	{
		this->currani = ani;
		this->currani->SetIndex(0);
	}
	int forcey = ani->GetForce()->first;
	int forcex = ani->GetForce()->second;
	this->AddForce(forcey,forcex);
}

void Movable::AddForce(int forcey, int forcex)
{
	this->force->first += forcey;
	this->force->second += forcex;
}

void Movable::AddTriggerForce()
{//
	//this->force->first -= 1;						//this group of functions shall be change to recive information from animations
	this->force->second -= 1;
}
//----------------------------------------
void Movable::AddSpeed()
{
	this->speed->first += this->force->first;
	this->speed->second += this->force->second;
	this->force->first = 0;
	this->force->second = 0;
}

void Movable::AddToPostion()
{
	if (this->id == 1)
		this->SetDst(this->dstpos->y + this->speed->first + 1, this->dstpos->x + this->speed->second);
	else
		this->SetDst(this->dstpos->y + this->speed->first, this->dstpos->x + this->speed->second);
}

void Movable::SetSpeed(int ySpeed, int xSpeed)
{
	this->speed->first = ySpeed;
	this->speed->second = xSpeed;
}
void Movable::SetDst(int y, int x) 
{
	this->dstpos->x = x;
	this->dstpos->y = y;
}
void Movable::SetForce(int forcey, int forcex)
{
	this->force->first = forcey;
	this->force->second = forcex;
}
SDL_Rect* Movable::GetDst() { return this->dstpos; }
pair<int, int>* Movable::GetForce() { return this->force; }
pair<int, int>* Movable::GetSpeed(){ return this->speed; }
Movable::~Movable()
{
}
