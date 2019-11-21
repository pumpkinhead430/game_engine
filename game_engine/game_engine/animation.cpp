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
