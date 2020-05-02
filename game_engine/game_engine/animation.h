#pragma once
#include <vector>
#include <chrono>
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
	bool defaultAnimation;
	double animationTime;
	std::chrono::steady_clock::time_point startClock;
public:
	animation(SDL_Renderer* renderer);
	animation(int damage, int trigger, int forcey, int forcex, string name, vector<string>* ani_starter, vector<Image*>* frames, bool defaultAnimation, double animationTime);
	Image* GetImage(int index);
	bool DefultAnimation();
	bool EndOfAnimation();
	bool IsTriggered(int input);
	double PictureTime();
	bool AniTimeUp();
	void ResetClock();
	vector<string>* GetAniStartes();
	string GetName();
	int GetDamage();
	int GetIndex();
	pair<int, int>* GetForce();
	void SetIndex(int index);
	~animation();
};

