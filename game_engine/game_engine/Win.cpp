#include "Win.h"

Win::Win(int startX, int endX, int startY, int endY, string action, int id, string type, int characterId)
{
	this->action = action;
	this->id = id;
	this->characterId = characterId;
	this->type = type;
	this->place->x = startX;
	this->place->y = startY;
	this->place->w = abs(endX - startX);
	this->place->h = abs(endY - startY);
}
