// test1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//y == first
//x == second

#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <chrono>
#include "Image.h"
#include "Movable.h"
#include "Stationary.h"
#include "Game.h"
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/istreamwrapper.h>
using namespace std;
using namespace rapidjson;
Game* game = nullptr;


Game* CreateGame(const Value& GameObject)
{
	int gravity = 0;
	int width = 10;
	int height = 10;
	const char* back_ground = "";
	bool fullscreen = false;
	const char* title = "";
	if (GameObject.IsObject())
	{ //check if object
		for (Value::ConstMemberIterator member = GameObject.MemberBegin(); member != GameObject.MemberEnd(); ++member)
		{   //iterate through object
			string nameOfmember = member->name.GetString();
			if (nameOfmember == "gravity")
				gravity = GameObject[member->name.GetString()].GetInt();

			if (nameOfmember == "width")
				width = GameObject[member->name.GetString()].GetInt();

			if (nameOfmember == "height")
				height = GameObject[member->name.GetString()].GetInt();

			if (nameOfmember == "background")
				back_ground = GameObject[member->name.GetString()].GetString();

			if (nameOfmember == "title")
				title = GameObject[member->name.GetString()].GetString();

			if (nameOfmember == "fullscreen")
				fullscreen = GameObject[member->name.GetString()].GetBool();

			if (nameOfmember == "default")
				return new Game("hello", 1000, 1000, false, "assets/default.png", 1);
		}
	}
	return new Game(title, width, height, fullscreen, back_ground, gravity);
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
	ifstream ifs("assets/GameData.json");
	IStreamWrapper isw(ifs);
	Document document;
	document.ParseStream(isw);
	game = CreateGame(document);
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
		std::cout << "\n" << (int)((double)1 / (duration * pow(10, -9)));
	}
	game->clean();
	return 0;

}