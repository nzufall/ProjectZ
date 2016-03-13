#include "Texture.h"


Texture::Texture(string x, SDL_Renderer* ren) {
	name = x;
	tex = loadTexture(name, ren);
}

SDL_Texture* Texture::loadTexture(const string &file, SDL_Renderer* ren) {
	//Initialize to nullptr to avoid dangling pointer issues
	SDL_Texture *texture = nullptr;
	//Load the image
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	//If the loading went ok, convert to texture and return the texture
	if (loadedImage != nullptr) {
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Make sure converting went ok too
		if (texture == nullptr) {
			std::cout << "ERROR: Failed to create texture from surface" << std::endl;
		}
	}
	else {
		std::cout << "ERROR: Failed to load Bitmap" << std::endl;
	}
	return texture;
}