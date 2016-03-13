#ifndef TILE_H
#define TILE_H
#include <iostream>
#include <string>
#include <SDL.h>
using namespace std;
class Tile {
public:
	/**
	* Creates a tile that can be rendered to the screen
	* @param x This is the boolean value for if the object has collision
	* @param y This is the textureID so it can be rendered correctly
	* @param z This is the name of the tile so it can be identified
	*/
	Tile(bool x, int y, string z, int h, int w);
	int tileID;
	string name;
	bool collides;
	int height;
	int width;

};

#endif /* TILE_H */
