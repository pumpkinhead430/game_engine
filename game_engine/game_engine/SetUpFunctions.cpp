#include "pch.h"
#include "Game.h"
using namespace rapidjson;
void Game::SetUp()
{
	/* this function will start the main game loop
	   and will prepare all of the objects ready for the game */
	
	VisableObj* temp = new VisableObj(this->renderer, new vector<string>{ "", "" }, "assets/defult.png", 0, 500, 0);
	stationaryobjs->push_back(temp);
	
	//-------------------------------------------
	/*
	animation* defult = new animation(this->renderer);
	vector<Image*>* frames = new vector<Image*>(0);
	frames->push_back(new Image("assets/UserR.bmp", this->renderer));
	frames->push_back(new Image("assets/UserWalR.bmp", this->renderer));
	animation* mov = new animation(3, SDL_GetScancodeFromName("s"), -10, 0, "jump", new vector<string>{ "jump", "MoveRight" }, frames);
	vector<Image*>* frames1 = new vector<Image*>(0);//setting first movable object
	frames1->push_back(new Image("assets/UserR.bmp", this->renderer));
	frames1->push_back(new Image("assets/UserWalR.bmp", this->renderer));
	//frames1->push_back(new Image("assets/BarrelA.bmp", this->renderer));
	animation* mov1 = new animation(0, SDL_GetScancodeFromName("d"), 0, 1, "walk", new vector<string>{ "MoveRight", "" }, frames1);
	vector <animation*>* animations = new vector<animation*>(0);
	animations->push_back(defult);
	animations->push_back(mov);
	animations->push_back(mov1);
	//-------------------------------------------
	//-------------------------------------------
	animation* defult1 = new animation(this->renderer);
	vector<Image*>* frames2 = new vector<Image*>(0);
	frames2->push_back(new Image("assets/UserR.bmp", this->renderer));
	frames2->push_back(new Image("assets/UserWalR.bmp", this->renderer));
	animation* mov2 = new animation(3, SDL_GetScancodeFromName("w"), 0, 1, "walk", new vector<string>{ "jump", "help" }, frames2);
	vector<Image*>* frames3 = new vector<Image*>(0); //setting second movable object
	frames3->push_back(new Image("assets/UserR.bmp", this->renderer));
	frames3->push_back(new Image("assets/UserWalR.bmp", this->renderer));
	//frames3->push_back(new Image("assets/BarrelA.bmp", this->renderer));
	animation* mov3 = new animation(3, SDL_SCANCODE_SPACE, -5, 0, "jump", new vector<string>{ "jump", "help" }, frames3);
	vector <animation*>* animations1 = new vector<animation*>(0);
	animations1->push_back(defult1);
	animations1->push_back(mov2);
	animations1->push_back(mov3);
	//-------------------------------------------------
	vector<Image*>* frames4 = new vector<Image*>(0);
	frames4->push_back(new Image("assets/defult.png", this->renderer));
	animation* mov4 = new animation(0, -2, 0, 1, "MoveRight", new vector<string>{ "", "" }, frames4);
	vector <animation*>* animations2 = new vector<animation*>(0);
	animations2->push_back(mov4);
	//-------------------------------------------
	movablechars->push_back(new Movable(this->renderer, 100, 15, 0, animations));
	movablechars->push_back(new Movable(this->renderer, 100, 0, 30, animations1));
	movablechars->push_back(new Movable(this->renderer, 1000000, 30, 60, animations2));
	*/
	ifstream ifs("D:/test.json");
	IStreamWrapper isw(ifs);
	Document document;
	document.ParseStream(isw);
	const Value& a = document["Movables"];
	assert(a.IsArray());
	for (int i = 0; i < stationaryobjs->size(); i++)
	{
		all_objects->push_back(stationaryobjs->at(i));
	}
	for (SizeType  i = 0; i < a.Size(); i++)
	{
		Movable* temp = GetMovableJson(a[i]);
		movablechars->push_back(temp);
		all_objects->push_back(temp);
		//all_objects->push_back(movablechars->at(i));
	}
}

animation*Game::GetAnimationJson(const Value& obj)
{
	int damage = 0;
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
			if (nameOfmember == "trigger")
				trigger = obj[member->name.GetString()].GetInt();
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
					
			if (nameOfmember == "defult")
				return new animation(this->renderer);
		}
	}
	return new animation(damage, trigger, forcey, forcex, name, ani_startes, frames);
}

Movable* Game::GetMovableJson(const Value& obj)
{
	int health = 0;
	int x = 0;
	int y = 0;
	vector<animation*> *animations = new vector<animation*>(0);
	if (obj.IsObject()) { //check if object
		for (Value::ConstMemberIterator member = obj.MemberBegin(); member != obj.MemberEnd(); ++member) 
		{   //iterate through object
			string nameOfmember = member->name.GetString();
			if (nameOfmember == "health")
			{
				health = obj[member->name.GetString()].GetInt();
			}
				
				
			if (nameOfmember == "x") 
			{
				x = obj[member->name.GetString()].GetInt();
			}
				
			if (nameOfmember == "y")
			{
				y = obj[member->name.GetString()].GetInt();
			}
			if (nameOfmember == "animations")
				for (SizeType i = 0; i < obj[member->name.GetString()].Size(); i++)
				{
					animations->push_back(GetAnimationJson(obj[member->name.GetString()][i]));
				}
					
			if (nameOfmember == "defult")
				return new Movable(this->renderer, 10, 0, 0);
		}
	}
	return new Movable(this->renderer, health, x, y, animations);
}