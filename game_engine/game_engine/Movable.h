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
	animation* currani = nullptr;
	SDL_Rect *dstpos = new SDL_Rect();
	void ActivateAnimation(animation* ani);
public:
	Movable(SDL_Renderer* renderer, int x, int y, vector<animation*>* animations);
	Movable(SDL_Renderer* renderer, int x, int y);
	void TriggerAnimation(int input);
	void ContinueAnimation();
	void AddTriggerForce();
	void AddSpeed();
	void AddToPostion();
	void AddForce(int forcey, int forcex);
	void SetSpeed(int ySpeed, int xSpeed);
	void SetDst(int y, int x);
	pair<int, int>* GetForce();
	void SetForce(int forcey, int forcex);
	pair<int, int>* GetSpeed();
	SDL_Rect * GetDst();
	~Movable();
};

