#pragma once
#include <vector>
#include "Image.h"
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
	animation();
	animation(int damage, int trigger, int forcey, int forcex, vector<Image*>* frames);
	int GetIndex();
	~animation();
};

