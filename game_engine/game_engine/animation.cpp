#include "pch.h"
#include "animation.h"
animation::animation(SDL_Renderer* renderer)
{
	this->index = 0;
	this->trigger = 26;
	this->force->first = 0;
	this->force->second = 1;
	this->frames->push_back(new Image("assets/defult.png", renderer));
	this->damage = 0;
}

animation::animation(int damage, int trigger,int forcey, int forcex, vector<Image*>* frames)
{
	this->index = 0;
	this->trigger = trigger;
	this->force->first = forcey;
	this->force->second = forcex;
	this->frames = frames;
	this->damage = damage;
}

Image* animation::GetImage(int index)
{
	return this->frames->at(index);
}

bool animation::EndOfAnimation()
{
	if(this->frames->size() == this->index)
		return true;
	return false;
}

bool animation::IsTriggered(int input)
{
	if (this->trigger == input)
		return true;
	return false;
}
int animation::GetIndex() { return this->index; }
pair<int, int>* animation::GetForce(){ return this->force; }
void animation::SetIndex(int index){ this->index = index; }
animation::~animation()
{
}
