#pragma once
#include <vector>
#include "Image.h"
#include "SDL.h"
#include "SDL_image.h"
using namespace std;
class animation
{
private:
	string name;
	int index;
	int trigger;
	vector<Image*>* frames = new vector<Image*>(0);
	vector<string>* ani_starter = new vector<string>(0);
	pair<int, int> *force = new pair<int, int>(0,0);
	int damage;
public:
	animation(SDL_Renderer* renderer);
	animation(int damage, int trigger, int forcey, int forcex, string name, vector<string>* ani_starter, vector<Image*>* frames);
	Image* GetImage(int index);
	bool DefultAnimation();
	bool EndOfAnimation();
	bool IsTriggered(int input);
	vector<string>* GetAniStartes();
	string GetName();
	int GetDamage();
	int GetIndex();
	pair<int, int>* GetForce();
	void SetIndex(int index);
	~animation();
};

