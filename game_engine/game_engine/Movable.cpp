#include "pch.h"
#include "Movable.h"


Movable::Movable(SDL_Renderer* renderer, int x, int y, vector<animation*>* animations) :VisableObj(renderer, x, y)
{//setting the trigger which will be in animations in due time and setting defult all speed and force
	this->dstpos->x = this->image_info->x;
	this->dstpos->y = this->image_info->y;
	this->dstpos->h = this->image_info->h;
	this->dstpos->w = this->image_info->w;
	this->animations = animations;
	for(int i = 0; i< this->animations->size(); i ++)
	{
		if(this->animations->at(i)->DefultAnimation())
		{
			this->current_image = this->animations->at(i)->GetImage(0);
			this->currani = this->animations->at(0);
		}
	}
	this->image_info->h = current_image->height;
	this->image_info->w = current_image->width;
	this->speed->first = 0;
	this->force->first = 0;
	this->speed->second = 0;
	this->force->second = 0;
}

Movable::Movable(SDL_Renderer* renderer, int x, int y) :VisableObj(renderer, x, y)
{//setting the trigger which will be in animations in due time and setting defult all speed and force
	this->animations->push_back(new animation(renderer));
	this->current_image = this->animations->at(0)->GetImage(0);
	this->image_info->h = current_image->height;
	this->image_info->w = current_image->width;
	this->currani = this->animations->at(0);
	this->dstpos->h = this->image_info->h;
	this->dstpos->w = this->image_info->w;
	this->dstpos->x = this->image_info->x;
	this->dstpos->y = this->image_info->y;
	this->speed->first = 0;
	this->force->first = 0;
	this->speed->second = 0;
	this->force->second = 0;
}

//--------------------------------------
void Movable::TriggerAnimation(int input)
{//cheking if animtaion is triggered
	for(int i = 0; i < this->animations->size(); i++)
	{
		if (this->animations->at(i)->IsTriggered(input))
		{
			this->ActivateAnimation(this->animations->at(i));
		}
	}
}



void Movable::ContinueAnimation()
{//continues current animation and brings it back to defult if animation ended
	if (this->currani->EndOfAnimation())
	{
		this->currani->SetIndex(0);		
		for (int i = 0; i < this->animations->size(); i++)
		{
			if (this->animations->at(i)->DefultAnimation())
			{
				this->currani = this->animations->at(i);
				this->AddForce(this->currani->GetForce()->first, this->currani->GetForce()->second);
				break;
			}
		}
	}
	else
	{
		this->currani->SetIndex(this->currani->GetIndex() + 1);
	}
	ChangeCurrentImage(this->currani->GetImage(this->currani->GetIndex()));
}



void Movable::ActivateAnimation(animation* ani)
{//strats the animation
	if (this->currani->DefultAnimation())
	{
		this->currani = ani;
		this->currani->SetIndex(0);
		ChangeCurrentImage(this->currani->GetImage(this->currani->GetIndex()));
	}
	int forcey = ani->GetForce()->first;
	int forcex = ani->GetForce()->second;
	this->AddForce(forcey,forcex);
}

void Movable::ChangeCurrentImage(Image* image)
{//changes current image
	this->current_image = image;
	this->image_info->h = this->current_image->height;
	this->image_info->w = this->current_image->width;
}

void Movable::AddForce(int forcey, int forcex)
{//adding force
	this->force->first += forcey;
	this->force->second += forcex;
}

void Movable::AddSpeed()
{//adding speed
	this->speed->first += this->force->first;
	this->speed->second += this->force->second;
	this->force->first = 0;
	this->force->second = 0;
}

void Movable::AddToPostion()
{//adds to the postion
	if (this->id == 1)
		this->SetDst(this->dstpos->y + this->speed->first + 1, this->dstpos->x + this->speed->second);
	else
		this->SetDst(this->dstpos->y + this->speed->first, this->dstpos->x + this->speed->second);
}
//sets and gets
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
