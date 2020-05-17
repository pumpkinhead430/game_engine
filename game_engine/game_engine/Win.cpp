#include "Win.h"

Win::Win(SDL_Renderer* renderer, int startX, int endX, int startY, int endY, string action, int id, string type, int characterId, string endImagePath)
{
	this->action = action;
	this->id = id;
	this->characterId = characterId;
	this->type = type;
	this->place->x = startX;
	this->place->y = startY;
	this->place->w = abs(endX - startX);
	this->place->h = abs(endY - startY);
	this->endImage = new Image(endImagePath, renderer);
}

bool Win::MetConditon(vector<Movable*>* movableObjects, vector<Movable*>* dead)
{
	Movable* movable = GetCharacter(movableObjects);
	if (movable != nullptr) {
		if (this->action == "place") {
			if (movable->In(place)) {
				return true;
			}
			return false;
		}
	}
	movable = GetCharacter(dead);
		if (movable != nullptr) {
			if (movable->GetHealth() <= 0) {
				return true;
			}

			return false;
		}
	return false;


}


Movable* Win::GetCharacter(vector<Movable*>* movableObjects) {
	for (int i = 0; i < movableObjects->size(); i ++) {
		if (movableObjects->at(i)->GetId() == this->characterId)
			return movableObjects->at(i);
	}
	return nullptr;
}

Image* Win::GetImage() {
	return this->endImage;
}

