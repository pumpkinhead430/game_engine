#include "pch.h"
#include "Game.h"
using namespace rapidjson;
void Game::SetUp()
{
	/* this function will start the main game loop
	   and will prepare all of the objects ready for the game */	
	//-------------------------------------------
	ifstream ifs("assets/objects.json");
	IStreamWrapper isw(ifs);
	Document document;
	document.ParseStream(isw);
	const Value& movable_objs = document["Movables"];
	const Value& stationary = document["Stationers"];
	for (int i = 0; i < stationary.Size(); i++)
	{
		this->stationaryobjs->push_back(GetStationaryJson(stationary[i]));
		this->all_objects->push_back(stationaryobjs->at(i));
	}
	for (SizeType  i = 0; i < movable_objs.Size(); i++)
	{
		this->movablechars->push_back(GetMovableJson(movable_objs[i]));
		this->all_objects->push_back(movablechars->at(i));
	}
}

animation* Game::GetAnimationJson(const Value& obj)
{
	int damage = 0;
	bool defaultAnimation = false;
	int forcex = 0;
	int forcey = 0;
	int trigger = 0;
	string temp = "";
	string name = "";
	vector<string>* ani_startes = new vector<string>(0);
	vector<Image*>* frames = new vector<Image*>(0);
	if (obj.IsObject()) { //check if object
		for (Value::ConstMemberIterator member = obj.MemberBegin(); member != obj.MemberEnd(); ++member)
		{   //iterate through object
			string nameOfmember = member->name.GetString();
			if (nameOfmember == "damage")
				damage = obj[member->name.GetString()].GetInt();
			if (nameOfmember == "name")
				name = obj[member->name.GetString()].GetString();
			if (nameOfmember == "trigger") {
				const char* temp = "";
				temp = obj[member->name.GetString()].GetString();
				trigger = SDL_GetScancodeFromName(temp);
			}
			if (nameOfmember == "forcex")
				forcex = obj[member->name.GetString()].GetInt();
			if (nameOfmember == "forcey")
				forcey = obj[member->name.GetString()].GetInt();
			if (nameOfmember == "frames")
				for (SizeType i = 0; i < obj[member->name.GetString()].Size(); i++)
				{
					temp = obj[member->name.GetString()][i].GetString();
					frames->push_back(new Image(temp, this->renderer));
				}		
			if (nameOfmember == "ani_starter")
				for (SizeType i = 0; i < obj[member->name.GetString()].Size(); i++)
				{
					temp = obj[member->name.GetString()][i].GetString();
					ani_startes->push_back(temp);
				}	
			if (nameOfmember == "default")
				defaultAnimation = obj[member->name.GetString()].GetBool();
		}
	}
	return new animation(damage, trigger, forcey, forcex, name, ani_startes, frames, defaultAnimation);
}

Movable* Game::GetMovableJson(const Value& obj)
{
	int health = 0;
	int x = 0;
	int y = 0;
	vector<animation*> *animations = new vector<animation*>(0);
	if (obj.IsObject()) 
	{ //check if object
		for (Value::ConstMemberIterator member = obj.MemberBegin(); member != obj.MemberEnd(); ++member) 
		{   //iterate through object
			string nameOfmember = member->name.GetString();
			if (nameOfmember == "health")
				health = obj[member->name.GetString()].GetInt();
					
			if (nameOfmember == "x") 
				x = obj[member->name.GetString()].GetInt();
				
			if (nameOfmember == "y")
				y = obj[member->name.GetString()].GetInt();

			if (nameOfmember == "animations")
				for (SizeType i = 0; i < obj[member->name.GetString()].Size(); i++)
					animations->push_back(GetAnimationJson(obj[member->name.GetString()][i]));

			if (nameOfmember == "default")
				return new Movable(this->renderer, 10, 0, 0);
		}
	}
	return new Movable(this->renderer, health, x, y, animations);
}

VisableObj* Game::GetStationaryJson(const Value& obj)
{
	int damage = 0;
	int x = 0;
	int y = 0;
	string path = "";
	vector<string>* curr_ani_start = new vector<string>(0);
	if (obj.IsObject()) { //check if object
		for (Value::ConstMemberIterator member = obj.MemberBegin(); member != obj.MemberEnd(); ++member)
		{   //iterate through object
			string nameOfmember = member->name.GetString();
			if (nameOfmember == "damage")
				damage = obj[member->name.GetString()].GetInt();

			if (nameOfmember == "path")
				path = obj[member->name.GetString()].GetString();

			if (nameOfmember == "x")
				x = obj[member->name.GetString()].GetInt();

			if (nameOfmember == "y")
				y = obj[member->name.GetString()].GetInt();

			if (nameOfmember == "ani_start")
				for (SizeType i = 0; i < obj[member->name.GetString()].Size(); i++)
				{
					curr_ani_start->push_back(obj[member->name.GetString()][i].GetString());
				}

			if (nameOfmember == "default")
				return new VisableObj(this->renderer,new vector<string>(0), "assets/default.png",0, 0, 0);
		}
	}
	return new VisableObj(this->renderer, curr_ani_start,path, x, y, damage);
}