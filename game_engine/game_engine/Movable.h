#pragma once
#include "VisableObj.h"
#include "animation.h"
#include <iostream>
class Movable : public VisableObj
{

private:
	int speed[2];
	int force[2];
	int trigger;
	SDL_Rect *dstpos = new SDL_Rect();
public:
	Movable(SDL_Renderer* renderer, string path, int x, int y, int trigger);
	bool Triggered(int input);
	void AddTriggerForce();
	void AddSpeed();
	void AddToPostion();
	void SetSpeed(int ySpeed, int xSpeed);
	void SetDst(int y, int x);
	int *GetForce();
	void SetForce(int forcey, int forcex);
	int GetSpeedX();
	int GetSpeedY();
	SDL_Rect * GetDst();
	~Movable();
};

