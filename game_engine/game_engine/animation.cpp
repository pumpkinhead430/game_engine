#include "pch.h"
#include "animation.h"
animation::animation(SDL_Renderer* renderer)
{
	this->index = 0;
	this->name = "";
	this->trigger = -1;
	this->force->first = 0;
	this->force->second = 0;
	this->frames->push_back(new Image("assets/defult.png", renderer));
	this->ani_starter->push_back("");
	this->damage = 0;
}

animation::animation(int damage, int trigger,int forcey, int forcex, string name, vector<string>* ani_starter,vector<Image*>* frames)
{
	this->index = 0;
	this->trigger = trigger;
	this->force->first = forcey;
	this->force->second = forcex;
	this->name = name;
	this->ani_starter = ani_starter;
	this->frames = frames;
	this->damage = damage;
}


bool animation::DefultAnimation()
{//checks if this animation is the defult animation
	if (this->trigger == -1)
		return true;
	return false;
}

bool animation::EndOfAnimation()
{//returns if the animation has ended or not
	if((int)this->frames->size() == this->index + 1)
		return true;
	return false;
}

bool animation::IsTriggered(int input)
{// this function checks whether the input is the animation's trigger
	if (this->trigger == input)
		return true;
	return false;
}
vector<string>* animation::GetAniStarters()
{
	return this->ani_starter;
}
//sets and gets
Image* animation::GetImage(int index){ return this->frames->at(index); }
int animation::GetIndex() { return this->index; }
pair<int, int>* animation::GetForce(){ return this->force; }
void animation::SetIndex(int index){ this->index = index; }
animation::~animation()
{
}
