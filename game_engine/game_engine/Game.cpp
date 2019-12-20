#include "pch.h"
#include "Game.h"
Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen, string background_path,int gravity)
{
	//initaing the game and everything in it
	int flags = 0;
	this->gravity = gravity;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		this->KeyInput = InputHandler();
		this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		this->renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		}
		this->background = new Image(background_path, this->renderer);
		this->background_rect->x = 0;
		this->background_rect->y = 0;
		this->background_rect->h = this->background->height;
		this->background_rect->w = this->background->width;
		isRunning = true;
	}
	this->SetUp();
}

void Game::handleEvents()
{
	//check if a event happens and inputs it to the iput handler	
	SDL_Event event;
	int lastcode = -1;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case(SDL_QUIT):
		{
			isRunning = false;
			break;
		}
		case(SDL_KEYDOWN):
		{
			int lastcode = event.key.keysym.scancode;
			this->KeyInput.SetState(event.key.keysym.scancode, event.key.state);
		}
		case(SDL_KEYUP):
		{
			if (lastcode != event.key.keysym.scancode)
				this->KeyInput.SetState(event.key.keysym.scancode, event.key.state);
		}
		}
	}
	for (int i = 0; i < this->KeyInput.GetKeys()->size(); i++)
	{
		if (this->KeyInput.GetKeys()->at(i) == SDL_PRESSED)
		{
			for (int j = 0; j < this->movablechars->size(); j++)
			{
				if (!this->movablechars->at(j)->InAir())
					this->movablechars->at(j)->TriggerAnimation(i);

			}

		}
	}
	//updating all the movable objects
	for (int i = 0; i < this->movablechars->size(); i++)
	{
		this->movablechars->at(i)->ContinueAnimation();
		this->movablechars->at(i)->SetForce(this->movablechars->at(i)->GetForce()->first + 1, this->movablechars->at(i)->GetForce()->second);
		this->movablechars->at(i)->AddSpeed();
		this->movablechars->at(i)->AddToPostion();
	}

}


void Game::render()
{
	//showing on screen all objects
	SDL_RenderClear(renderer);
	SDL_RenderCopy(this->renderer, this->background->GetImage(), NULL, this->background_rect);
	for(int i = 0; i<this->all_objects->size(); i++)
	{
		SDL_RenderCopy(this->renderer, this->all_objects->at(i)->GetCurrentImage()->GetImage(), NULL, this->all_objects->at(i)->GetInfo());
		Movable* temp = dynamic_cast<Movable*>(all_objects->at(i));
		if(temp)
		{
			temp->SetXPos(temp->GetDst()->x);
			temp->SetYPos(temp->GetDst()->y);
		}
	}
	SDL_RenderPresent(this->renderer);
}

bool Game::IsDead(VisableObj* object)
{
	for (int i = 0; i < dead->size(); i++)
	{
		if (dead->at(i) == object)
			return true;
	}
	return false;
}

void Game::GetDead()
{
	for (int i = 0; i < movablechars->size(); i++)
	{
		if (movablechars->at(i)->GetHealth() <= 0)
		{
			dead->push_back(movablechars->at(i));
			for (int j = 0; j < all_objects->size(); j++)
				if (all_objects->at(j) == movablechars->at(i))
					all_objects->erase(remove(all_objects->begin(), all_objects->end(), all_objects->at(j)), all_objects->end());
			movablechars->erase(remove(movablechars->begin(), movablechars->end(), movablechars->at(i)), movablechars->end());

		}
	}
}

void Game::SetUp()
{
	/* this function will start the main game loop
	   and will prepare all of the objects ready for the game */
	VisableObj* temp = new VisableObj(this->renderer, new vector<string>{ "", "" }, "assets/defult.png", 0, 500, 0);
	stationaryobjs->push_back(temp);
	//-------------------------------------------
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

	for (int i = 0; i < stationaryobjs->size(); i++)
	{
		all_objects->push_back(stationaryobjs->at(i));
	}
	for (int i = 0; i < movablechars->size(); i++)
	{
		all_objects->push_back(movablechars->at(i));
	}
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