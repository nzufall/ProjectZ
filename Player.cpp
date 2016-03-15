#include "Player.h"

#include <SDL.h>
#include <iostream>
#include <vector>
#include "Tile.h"
#include "Level.h"

Player::Player() {
	x = 40;
	y = 40;
	health = 100;
	hitTime = 0;
	vSpeed = 0;
	hSpeed = 0;
	shootCount = 0;
	textureID = 0;
	jumping = true;
	int direction = 1;
}
int Player::collidingX(vector<Tile> Tiles, vector<Level> levels) {
	// 0 - not colliding
	// 1 - colliding from right
	// -1 - colliding from left


	//check level edge collision
	if (x + hSpeed < 0) {
		x = 1;
		hSpeed = 0;
		if (y + vSpeed < 0) {
			y = 1;
			vSpeed = 0;

		}
		if (y + vSpeed + 64 > levels.at(0).height * 32) {
			y = (levels.at(0).height * 32) - 67;
			vSpeed = 0;
			jumping = false;

		}

		return -1;

	}
	if (x + hSpeed + 32 > levels.at(0).width * 32) {
		x = levels.at(0).width * 32 - 34;
		hSpeed = 0;
		if (y + vSpeed < 0) {
			y = 1;
			vSpeed = 0;
			
		}
		if (y + vSpeed + 64 > levels.at(0).height * 32) {
			y = (levels.at(0).height * 32) - 67;
			vSpeed = 0;
			jumping = false;
			
		}

		return 1;

	}

	if (levels.at(0).getNode((x + hSpeed) / 32 + 1, ((y) / 32)) >= 0) {
		hSpeed = 0;
		return 1;
	}
	if (levels.at(0).getNode((x + hSpeed) / 32 - 1, ((y) / 32)) >= 0) {
		hSpeed = 0;
		return -1;
	}
	//check level collisions
	
	return 0;
}
int Player::collidingY(vector<Tile> Tiles, vector<Level> levels) {
	// 0 - not colliding
	// 2 - colliding with ground
	// -2 - upper collision

	//check level edge collision

	if (y + vSpeed < 0) {
		y = 1;
		vSpeed = 0;
		return -2;
	}
	if (y + vSpeed + 64 > levels.at(0).height * 32) {
		y = (levels.at(0).height * 32) - 64;
		vSpeed = 0;
		jumping = false;
		return 2;
	}


	//check level collisions
	if (levels.at(0).getNode((x) / 32, ((y + vSpeed + 32) / 32 + 1)) >= 0) {

		if (Tiles.at(levels.at(0).getNode((x / 32), ((y + vSpeed + 32) / 32) + 1)).collides) {
			jumping = false;
			vSpeed = 0;

			return 2;
		}
		else if (Tiles.at(levels.at(0).getNode((x / 32), ((y + vSpeed + 32) / 32) - 1)).collides) {
			vSpeed = 0;
			return -2;
		}


	}
	return 0;
}
void Player::update(vector<Tile> &Tiles, vector<Level> &levels) {
	//gravity
	shootCount++;
	hitTime++;
		vSpeed += 10;
		if (vSpeed > 50) {
			vSpeed = 50;
		}
	//input
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			SDL_Quit();
			exit(1);
			return;
		}
		if (event.type == SDL_KEYDOWN) {
			input.keyPressed(event);
		}
		if (event.type == SDL_KEYUP) {
			input.keyReleased(event);
		}
	}
	if (input.keyState(SDL_SCANCODE_D)) {
		direction = 1;
		hSpeed += 8;

	}
	if (input.keyState(SDL_SCANCODE_A)) {
		direction = -1;
		hSpeed -= 8;
	}
	if (input.keyState(SDL_SCANCODE_W) && !jumping) {
		jumping = true;
		vSpeed = -50;
	}
	if (input.keyState(SDL_SCANCODE_E) && shootCount > 15) {
		shootCount = 0;
		shooting = true;
	}
	if (input.keyState(SDL_SCANCODE_ESCAPE)) {
		SDL_Quit();
		exit(1);
	}
	

	//Applying Input and Collisions
	int collisionX = collidingX(Tiles, levels);
	int collisionY = collidingY(Tiles, levels);

	if (collisionY == 2) {
		jumping = false;
	}
	if (collisionX == 0 && collisionY == 0) {
		if (vSpeed < 0) {
			y += vSpeed;
		}

		if (hSpeed > 31) {
			hSpeed = 31;
		}
		if (hSpeed < -31) {
			hSpeed = -31;
		}
		x += hSpeed;
		y += vSpeed;
		vSpeed += 5;

		if (hSpeed > 0) {
			hSpeed -= 5;
			if (hSpeed < 5) hSpeed = 0;
		}
		else if (hSpeed < 0) {
			hSpeed += 5;
			if (hSpeed > -5) hSpeed = 0;
		}
	}
	if (collisionY == 2 || collisionY == -2) {
		x += hSpeed;
		if (hSpeed > 0) {
			hSpeed -= 5;
			if (hSpeed < 5) hSpeed = 0;
		}
		else if (hSpeed < 0) {
			hSpeed += 5;
			if (hSpeed > -5) hSpeed = 0;
		}
	}
	if (collisionX == 1 || collisionX == -1) {
		if (collisionY != 2) {
			y += vSpeed;
			vSpeed += 5;
		}
	}
}