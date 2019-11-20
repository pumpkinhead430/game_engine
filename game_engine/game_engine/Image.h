#pragma once
#include <iostream>
#include <vector>
#include<array>
#include "SDL.h"
#include "Image.h"
#include "SDL_image.h"
using namespace std;
class Image
{
private:
	SDL_Texture *image;
	vector<int>*alpha = new vector<int>(0);
	vector<array<int, 2>> *collision_pixels = new vector<array<int, 2>>(0);

	Uint32 getPixel(SDL_Surface *loadingSurface, int x, int y);
	int GetAlpha(SDL_Surface* surface, int y, int x);
public:
	int height, width;
	Image(string path, SDL_Renderer *renderer);
	bool IsTransperent(int i, int j);
	vector<int>* GetAlphaChannel();
	vector<array<int, 2>>* GetCollisonPixels();
	void SetCollisonPixels();
	SDL_Texture* GetImage();
	~Image();
};

