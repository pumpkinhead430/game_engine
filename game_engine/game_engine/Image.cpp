#include "pch.h"
#include "Image.h"



Image::Image(string path, SDL_Renderer *renderer)
{
	const char *char_path = path.c_str();
	SDL_Surface *tmp_surface = IMG_Load(char_path);
	this->image = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	this->height = tmp_surface->h;
	this->width = tmp_surface->w;
	if (tmp_surface->format->Amask != 0)
	{
		//getting all of the alpha values of each pixels
		for (int i = 0; i < this->height; i++)
		{
			for (int j = 0; j < this->width; j++)
			{
				this->alpha->push_back(GetAlpha(tmp_surface, i, j));
			}
		}
	}
	SDL_FreeSurface(tmp_surface);
	SetCollisonPixels();
}


bool Image::IsTransperent(int i, int j)
{// this function checks if a pixel is transperent via alpha channel and returns true if it is and false otherwise
	if (this->alpha->size() > 2)
	{
		if (this->alpha->at(i * this->width + j) == 0)
			return true;
		return false;
	}
	return false;
}


Uint32 Image::getPixel(SDL_Surface *loadingSurface, int y, int x) {
	Uint32 *pixels = (Uint32*)loadingSurface->pixels;
	return pixels[(y * loadingSurface->pitch / 4) + x];

}

int Image::GetAlpha(SDL_Surface* surface, int y, int x)
{
	//getting alpha value of pixel (x,y)
	SDL_Color getColor = { 0,0,0 };
	SDL_PixelFormat *format;
	Uint32 pixel, index;
	Uint8 red, green, blue, alpha;
	format = surface->format;
	SDL_LockSurface(surface);
	pixel = getPixel(surface, y, x);
	SDL_UnlockSurface(surface);
	index = pixel & format->Amask;
	index = index >> format->Ashift;
	index = index << format->Aloss;
	alpha = (Uint8)index;
	getColor.a = alpha;
	return getColor.a;
}


vector<int>* Image::GetAlphaChannel()
{
	return this->alpha;
}

void Image::SetCollisonPixels()
{
	//getting all pixels of frame of the image
	//#pragma omp parallel for
	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
		{
			if (!IsTransperent(i, j))
			{
				if ((i == 0 || i == this->height - 1) || (j == 0 || j == this->width - 1))// checks if it is in the edges of the picture
				{
					//#pragma omp	critical
					//{
					this->collision_pixels->push_back({ i, j });
					//}

				}
				else
					// checks if around the pixel there is a transperent pixel
					if (IsTransperent(i, j + 1) || IsTransperent(i, j - 1) || IsTransperent(i - 1, j) || IsTransperent(i + 1, j))
					{
						//#pragma omp	critical
						//{
						this->collision_pixels->push_back({ i, j });
						//}
					}
			}

		}
}



vector<array<int, 2>>* Image::GetCollisonPixels() { return this->collision_pixels; }
SDL_Texture* Image::GetImage() { return this->image; }


Image::~Image()
{
}
