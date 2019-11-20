#include "pch.h"
#include "InputHandler.h"


InputHandler::InputHandler()
{
	for (int i = 0; i < this->KeyState->size(); i++)
	{
		this->KeyState->at(i) = SDL_RELEASED;
	}
}

int InputHandler::GetKeyState(int scancode)
{
	return this->KeyState->at(scancode);
}
vector<int>* InputHandler::GetKeys()
{
	return this->KeyState;
}
void InputHandler::SetState(int scancode, int state)
{
	//cahnging the key state of a realeased or pressed button
	this->KeyState->at(scancode) = state;
}

InputHandler::~InputHandler()
{
}
