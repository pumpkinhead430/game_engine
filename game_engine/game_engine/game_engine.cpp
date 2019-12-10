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
	const int FPS = 60;
	const int frameDealy = 1000 / FPS;
	Uint32 framestart;
	Uint32 frametime;
	//
	// creating game and objects of the game
	game = new Game();
	game->init("hello", 1000, 1000, false);
	Stationary* temp = new Stationary(3, game->GetRenderer(), new vector<string>{ "jump", "help" },"assets/BarrelA.bmp", 30, 30);
	stationaryobjs->push_back(temp);
	//-------------------------------------------
	animation* defult = new animation(game->GetRenderer());
	vector<Image*>* frames = new vector<Image*>(0);
	frames->push_back(new Image("assets/UserR.bmp", game->GetRenderer()));
	frames->push_back(new Image("assets/UserWalR.bmp", game->GetRenderer()));
	animation *mov = new animation(3, SDL_GetScancodeFromName("s"), 0, -1, "walk", new vector<string>{"jump", "help"}, frames);
	vector<Image*>* frames1 = new vector<Image*>(0);//setting first movable object
	frames1->push_back(new Image("assets/trans_cubes.png", game->GetRenderer()));
	frames1->push_back(new Image("assets/line.png", game->GetRenderer()));
	frames1->push_back(new Image("assets/BarrelA.bmp", game->GetRenderer()));
	animation* mov1 = new animation(3, SDL_GetScancodeFromName("d"), 0, 0,"walk", new vector<string>{ "jump", "help" }, frames1);
	vector <animation*>* animations = new vector<animation*>(0);
	animations->push_back(defult);
	animations->push_back(mov);
	animations->push_back(mov1);
	//-------------------------------------------
	//-------------------------------------------
	animation* defult1 = new animation(game->GetRenderer());
	vector<Image*>* frames2 = new vector<Image*>(0);
	frames2->push_back(new Image("assets/UserR.bmp", game->GetRenderer()));
	frames2->push_back(new Image("assets/UserWalR.bmp", game->GetRenderer()));
	animation* mov2 = new animation(3, SDL_GetScancodeFromName("w"), 0, 1,"walk", new vector<string>{ "jump", "help" }, frames2);
	vector<Image*>* frames3 = new vector<Image*>(0); //setting second movable object
	frames3->push_back(new Image("assets/trans_cubes.png", game->GetRenderer()));
	frames3->push_back(new Image("assets/line.png", game->GetRenderer()));
	frames3->push_back(new Image("assets/BarrelA.bmp", game->GetRenderer()));
	animation* mov3 = new animation(3, SDL_SCANCODE_SPACE, -1, 0, "jump", new vector<string>{ "jump", "help" }, frames3);
	vector <animation*>* animations1 = new vector<animation*>(0);
	animations1->push_back(defult1);
	animations1->push_back(mov2);
	animations1->push_back(mov3);
	//-------------------------------------------
	movablechars->push_back(&Movable(game->GetRenderer(), 0, 0, animations));
	movablechars->push_back(&Movable(game->GetRenderer(), 0, 400, animations1));
	SetUp();
	while (game->running())
	{
		auto t1 = std::chrono::high_resolution_clock::now();
		framestart = SDL_GetTicks();
		game->handleEvents(movablechars);
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

