#ifndef GAME_H
#define GAME_H


#include <SDL.h>
#include "Texture.h"
#include "Tile.h"
#include "Camera.h"
#include "Player.h"
#include "Level.h"
#include <iostream>
#include <string>
#include <vector>



using namespace std;
class Game {
public:
	//Constructors
	/**
	*	Baseline Constructor
	*/
	Game();

	//Functions
	/**
	*	Runs start of game things to set up the game.
	*/
	void Startup();
	/**
	* Main Game Loop
	*/
	void run();
	/**
	* updates all game objects
	*/
	void update();
	/**
	* pushes all appropriate graphics to the display
	*/
	void render();
	/**
	* loads all textures that will be used for game to memory. Not efficent but will work for now
	*/
	void loadAllAssets();
	/**
	* Loads a BMP image into a texture on the rendering device
	* @param file The BMP image file to load
	* @param ren The renderer to load the texture onto
	* @return the loaded texture, or nullptr if something went wrong.
	*/
	SDL_Texture* loadTexture(const string &file, SDL_Renderer* ren);
	/**
	* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
	* the texture's width and height
	* @param tex The source texture we want to draw
	* @param ren The renderer we want to draw to
	* @param x The x coordinate to draw to
	* @param y The y coordinate to draw to
	*/
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
	//Variables
	vector<Texture> vTextures;
	vector<Tile> vTiles;
	vector<Level> vLevels;
	Camera* cam;
	Player player;
	int vTexSize;
	SDL_Window *window;
	SDL_Renderer *renderer;
	string gameTitle;
	string resPath;
	int SCREEN_HEIGHT;
	int SCREEN_WIDTH;
	bool running;
private:
};

//<Nik> <is> <well> <loved> ();
#endif //GAME_H