#ifndef ENEMY_H
#define ENEMY_H 

#include <SDL.h>
#include <string>
using namespace std;
class Enemy {
public:
	Enemy();
	int x;
	int y;
	SDL_Texture* tex;
	string name;
	void update(int pX, int pY);
private:

};
#endif // !ENEMY_H
