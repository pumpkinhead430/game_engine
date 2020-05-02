#include "pch.h"
#include "animation.h"
animation::animation(SDL_Renderer* renderer)
{
	this->index = 0;
	this->name = "";
	this->trigger = -1;
	this->force->first = 0;
	this->force->second = 0;
	this->frames->push_back(new Image("assets/UserR.bmp", renderer));
	this->ani_starter->push_back("");
	this->damage = 0;
	this->defaultAnimation = false;
}

animation::animation(int damage, int trigger,int forcey, int forcex, string name, vector<string>* ani_starter,vector<Image*>* frames, bool defaultAnimation, double animationTime)
{
	this->startClock = std::chrono::high_resolution_clock::now();
	this->index = 0;
	this->trigger = trigger;
	this->force->first = forcey;
	this->force->second = forcex;
	this->name = name;
	this->defaultAnimation = defaultAnimation;
	this->ani_starter = ani_starter;
	this->frames = frames;
	this->damage = damage;
	this->animationTime = animationTime;
}


bool animation::DefultAnimation()
{//checks if this animation is the default animation
	return defaultAnimation;
}

bool animation::EndOfAnimation()
{//returns if the animation has ended or not
	if((int)this->frames->size() == this->index + 1)
	{
		return true;
	}
	return false;
}

bool animation::IsTriggered(int input)
{// this function checks whether the input is the animation's trigger
	if (this->trigger == input)
		return true;
	return false;
}

double animation::PictureTime() {
	return (double)animationTime / (double)frames->size();
}

bool animation::AniTimeUp() {
	std::chrono::steady_clock::time_point temp = std::chrono::high_resolution_clock::now();
	double duration = std::chrono::duration_cast<std::chrono::milliseconds>(temp - startClock).count();
	if (duration > PictureTime())
		return true;
	return false;
}

void animation::ResetClock() {
	this->startClock = std::chrono::high_resolution_clock::now();
}


//sets and gets
vector<string>* animation::GetAniStartes() { return this->ani_starter; }
string animation::GetName() { return this->name; }
int animation::GetDamage() { return this->damage; }
Image* animation::GetImage(int index){ return this->frames->at(index); }
int animation::GetIndex() { return this->index; }
pair<int, int>* animation::GetForce(){ return this->force; }
void animation::SetIndex(int index){ this->index = index; }
animation::~animation()
{
}
