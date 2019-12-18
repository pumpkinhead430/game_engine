// test1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//y == first
//x == second

#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include "Game.h"
#include "Movable.h"
#include "Image.h"
#include <chrono>
#include "Stationary.h"
using namespace std;
Game* game = nullptr;


int main(int argc, char* args[])
{
	// limiting frames per second
	const int FPS = 60;
	const int frameDealy = 1000 / FPS;
	Uint32 framestart;
	Uint32 frametime;
	//
	// creating game and objects of the game
	game = new Game();
	game->init("hello", 1000, 1000, false,"assets/Broken.jpg",1);
	while (game->running())
	{
		auto t1 = std::chrono::high_resolution_clock::now();
		framestart = SDL_GetTicks();
		game->handleEvents();
		game->collision();
		game->GetDead();
		game->render();
		frametime = SDL_GetTicks() - framestart;
		if (frameDealy > frametime)
		{
			SDL_Delay(frameDealy - frametime);
		}
		auto t2 = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
		std::cout << "\n" <<   (int)((double)1 / (duration * pow(10,-9)));
	}
	game->clean();
	return 0;

}