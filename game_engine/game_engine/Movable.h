#pragma once
#include "VisableObj.h"
#include "animation.h"
#include <iostream>
class Movable : public VisableObj
{

private:
	pair<int, int>* speed = new pair<int, int>(0, 0);
	pair<int, int>* force = new pair<int, int>(0, 0);
	vector<animation*>*animations = new vector<animation*>(0);
	SDL_Rect *dstpos = new SDL_Rect();
public:
	Movable(SDL_Renderer* renderer, string path, int x, int y, vector<animation*> *animations);
	bool Triggered(int input);
	void AddTriggerForce();
	void AddSpeed();
	void AddToPostion();
	void SetSpeed(int ySpeed, int xSpeed);
	void SetDst(int y, int x);
	pair<int, int>* GetForce();
	void SetForce(int forcey, int forcex);
	pair<int, int>* GetSpeed();
	SDL_Rect * GetDst();
	~Movable();
};

