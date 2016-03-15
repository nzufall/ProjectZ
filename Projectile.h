#ifndef PROJECTILE_H
#define PROJECTILE_H

class Projectile {
public:
	/**
	* Constructor
	* @param x sets the point of origination for x
	* @param y sets the point of origination for y
	* @param dir sets the direction of travel
	*/
	Projectile(int x, int y, int dir);
	bool friendly;
	int direction;
	int originX;
	int originY;
	int x;
	int y;
	/**
	* If a certain amount of time passes or if the projectile travels so far it end the projectiles instance.
	*/
	bool killProjectile();
	/**
	* Updates the position of the projectile
	*/
	void update();
	int time;

private:

};
#endif // !PROJECTILE_H
