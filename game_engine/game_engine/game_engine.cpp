// test1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include "Game.h"
#include "Movable.h"
#include "Image.h"
#include <chrono>
#include "Stationary.h"
#include "CollisionFunctions.h"
using namespace std;
vector<Movable*>* movablechars = new vector<Movable*>(0);//all Movable objects
vector<Stationary*>* stationaryobjs = new vector<Stationary*>(0);//all Stationary objects
vector<VisableObj*>* all_objects = new vector<VisableObj*>(0);//all visable objects
vector<VisableObj*>* colided = new vector<VisableObj*>(0);// all colided objects
Game* game = nullptr;



void SetUp()
{
	/* this function will start the main game loop
	   and will prepare all of the objects ready for the game */
	
	for (int i = 0; i < stationaryobjs->size(); i++)
	{
		all_objects->push_back(stationaryobjs->at(i));
	}
	for (int i = 0; i < movablechars->size(); i++)
	{
		all_objects->push_back(movablechars->at(i));
	}
}

int main(int argc, char* args[])
{
	// limiting frames per second
	const int FPS = 144;
	const int frameDealy = 1000 / FPS;
	Uint32 framestart;
	Uint32 frametime;
	//
	// creating game and objects of the game
	game = new Game();
	game->init("hello", 1000, 1000, false);
	Stationary* temp = new Stationary(3, game->GetRenderer(), "assets/BarrelA.bmp", 30, 30);
	stationaryobjs->push_back(temp);
	movablechars->push_back(&Movable(game->GetRenderer(), "assets/trans_cubes.png", 700, 100, nullptr));
	movablechars->push_back(&Movable(game->GetRenderer(), "assets/unicorn.png", 0, 400, nullptr));
	SetUp();
	//
	//starting game loop
	while (game->running())
	{
		auto t1 = std::chrono::high_resolution_clock::now();
		framestart = SDL_GetTicks();
		game->handleEvents(movablechars);
		game->update(movablechars);
		collision(all_objects, movablechars, colided);
		//prints all sides an objects has been hit 
		game->render(movablechars, stationaryobjs);
		frametime = SDL_GetTicks() - framestart;
		if (frameDealy > frametime)
		{
			SDL_Delay(frameDealy - frametime);
		}
		auto t2 = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
		//std::cout << "\n" << duration * pow(10,-9);
	}
	game->clean();
	return 0;

}

