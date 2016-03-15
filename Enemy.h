#ifndef ENEMY_H
#define ENEMY_H 

#include <SDL.h>
#include <string>
using namespace std;
class Enemy {
public:
	/**
	* default Constructor. Sets enemy health
	*/
	Enemy();
	int x;
	int y;
	int health;
	SDL_Texture* tex;
	string name;
	/**
	* when the player is in range of the enemy, it moves the enemy in the direction that the player is. 
	* @param pX gives the players current location for updating purposes (X)
	* @param pY gives the players current location for updating purposes (Y)
	*/
	void update(int pX, int pY);
private:

};
#endif // !ENEMY_H
