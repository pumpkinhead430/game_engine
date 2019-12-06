#include "pch.h"
#include "Game.h"
Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	//initaing the game and everything in it
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		KeyInput = InputHandler();
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		}

		isRunning = true;
	}
}

void Game::handleEvents(vector<Movable*> *movobj)
{
	//check if a event happens and acts by it
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		this->KeyInput.SetState(event.key.keysym.scancode, event.key.state);
	case SDL_KEYUP:
		this->KeyInput.SetState(event.key.keysym.scancode, event.key.state);
	}
	for (int i = 0; i < movobj->size(); i++)
	{
		movobj->at(i)->ContinueAnimation();
		movobj->at(i)->AddSpeed();
		movobj->at(i)->AddToPostion();
	}
	for (int i = 0; i < this->KeyInput.GetKeys()->size(); i++)
	{
		if (this->KeyInput.GetKeys()->at(i) == SDL_PRESSED)
		{
			for (int j = 0; j < movobj->size(); j++)
			{
				movobj->at(j)->TriggerAnimation(i);

			}
				
		}
	}
			
		

}


void Game::render(vector<Movable*>*canmove, vector<Stationary*>* stationary)
{
	//showing on screen all objects
	SDL_RenderClear(renderer);
	for (int i = 0; i < canmove->size(); i++)
	{
			SDL_RenderCopy(this->renderer, canmove->at(i)->GetCurrentImage()->GetImage(), NULL, canmove->at(i)->GetInfo());
			canmove->at(i)->SetXPos(canmove->at(i)->GetDst()->x);
			canmove->at(i)->SetYPos(canmove->at(i)->GetDst()->y);
	}
	for (int i = 0; i < stationary->size(); i++)
	{
		SDL_RenderCopy(this->renderer, stationary->at(i)->GetCurrentImage()->GetImage(), NULL, stationary->at(i)->GetInfo());
	}
	SDL_RenderPresent(this->renderer);
}


SDL_Renderer* Game::GetRenderer()
{
	return this->renderer;
}

bool Game::running() { return isRunning; }

void Game::clean()
{
	//finishes game and destroyes window
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}