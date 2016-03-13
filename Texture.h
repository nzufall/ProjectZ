#ifndef TEXTURE_H
#define TEXTURE_H
#include <iostream>
#include <string>
#include <SDL.h>
using namespace std;
class Texture {
public:
	/**
	* Constructor and Inits the texture. Textures go into a vector
	* @param x file name for the texture and solid identifier
	* @param y actual texture that is being loaded
	*/
	Texture(string x, SDL_Renderer* ren);

	/**
	* Loads a BMP image into a texture on the rendering device
	* @param file The BMP image file to load
	* @param ren The renderer to load the texture onto
	* @return the loaded texture, or nullptr if something went wrong.
	*/
	SDL_Texture* loadTexture(const string &file, SDL_Renderer* ren);
	string name;
	SDL_Texture* tex;
private:
};

#endif /* TEXTURE_H */
