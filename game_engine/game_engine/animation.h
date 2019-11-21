#pragma once
#include <vector>
#include "Image.h"
#include "SDL.h"
#include "SDL_image.h"
using namespace std;
class animation
{
private:
	int index;
	int trigger;
	vector<Image*>* frames = new vector<Image*>(0);
	pair<int, int> *force = new pair<int, int>(0,0);
	int damage;
public:
	animation(SDL_Renderer* renderer);
	animation(int damage, int trigger, int forcey, int forcex, vector<Image*>* frames);
	bool IsTriggered(int input);
	int GetIndex();
	pair<int, int>* GetForce();
	void SetIndex(int index);
	~animation();
};

