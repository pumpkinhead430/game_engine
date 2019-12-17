#pragma once
#include "VisableObj.h"
#include "animation.h"
#include <iostream>
class Movable : public VisableObj
{

private:
	int health;
	bool in_air;
	pair<int, int>* speed = new pair<int, int>(0, 0);
	pair<int, int>* force = new pair<int, int>(0, 0);
	vector<animation*>*animations = new vector<animation*>(0);
	animation* currani = nullptr;
	SDL_Rect *dstpos = new SDL_Rect();
	void ChangeCurrentImage(Image* image);
	void ChangeAnimation(animation* ani);
public:
	Movable(SDL_Renderer* renderer, int health,int x, int y, vector<animation*>* animations);
	Movable(SDL_Renderer* renderer, int health,int x, int y);
	void ActivateAnimation(animation* ani);
	void TriggerAnimation(int input);
	void ContinueAnimation();
	bool InAir();
	void Air(bool air);
	void AddSpeed();
	void AddToPostion();
	void AddForce(int forcey, int forcex);
	void SetSpeed(int ySpeed, int xSpeed);
	void SetDst(int y, int x);
	void SetHealth(int health);
	int GetHealth();
	string GetType();
	pair<int, int>* GetForce();
	vector<animation*>* GetAnimations();
	void SetForce(int forcey, int forcex);
	pair<int, int>* GetSpeed();
	SDL_Rect * GetDst();
	~Movable();
};

