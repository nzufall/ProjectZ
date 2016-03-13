#ifndef PLAYER_H
#define PLAYER_H

#include "Input.h"
#include <vector>
#include "Tile.h"
#include "Level.h"
class Player {
public:
	Player();


	int x;
	int y;
	int hSpeed;
	int vSpeed;
	int textureID;
	bool jumping;
	void update(vector<Tile> &Tiles, vector<Level> &levels);
	int collidingX(vector<Tile> Tiles, vector<Level> levels);
	int collidingY(vector<Tile> Tiles, vector<Level> levels);
	Input input;
private:
	

};
#endif // !PLAYER_H
