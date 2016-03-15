#ifndef PLAYER_H
#define PLAYER_H

#include "Input.h"
#include <vector>
#include "Tile.h"
#include "Level.h"
class Player {
public:
	/**
	* Default Constructor
	* Sets starting parameters
	*/
	Player();

	int direction;
	int x;
	int y;
	int health;
	int hitTime;
	int hSpeed;
	int vSpeed;
	int textureID;
	bool jumping;
	bool shooting; 
	int shootCount;
	/**
	* Updates the player and handles input from the input class
	* @param tiles passes by reference a vector of Tiles that the player may collide with
	* @param levels passes the location of tiles so that collision can be determined
	*/
	void update(vector<Tile> &Tiles, vector<Level> &levels);
	/**
	* Recieves the passed parameters from the update function to address how collisions will be handled
	* @param tiles passes by reference a vector of Tiles that the player may collide with
	* @param levels passes the location of tiles so that collision can be determined
	*/
	int collidingX(vector<Tile> Tiles, vector<Level> levels);
	/**
	* Recieves the passed parameters from the update function to address how collisions will be handled
	* @param tiles passes by reference a vector of Tiles that the player may collide with
	* @param levels passes the location of tiles so that collision can be determined
	*/
	int collidingY(vector<Tile> Tiles, vector<Level> levels);
	Input input;
private:
	

};
#endif // !PLAYER_H
