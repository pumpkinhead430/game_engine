#pragma once
#include <iostream>
#include "SDL.h"
#include <vector>
using namespace std;
class InputHandler
{
private:
	vector<int>* KeyState = new vector<int>(284);
public:
	InputHandler();
	int GetKeyState(int ScanCode);
	vector<int>* GetKeys();
	void SetState(int scancode, int state);
	~InputHandler();
};

