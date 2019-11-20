#include "pch.h"
#include "animation.h"


animation::animation()
{
	this->index = 0;
	this->trigger = -1;
	this->frames = nullptr;
	this->damage = 0;
}

animation::animation(int damage, int trigger,int forcey, int forcex, vector<Image*>* frames)
{
	this->index = 0;
	this->trigger = trigger;
	this->force = &make_pair(forcey, forcex);
	this->frames = frames;
	this->damage = damage;
}



int animation::GetIndex() { return this->index; }
animation::~animation()
{
}
