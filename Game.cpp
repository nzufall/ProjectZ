#include "Game.h"



Game::Game() {
	//Initialize Game Variables here
	running = false;
	gameTitle = "Project Z";
	vTexSize = 0;
	SCREEN_HEIGHT = 768;
	SCREEN_WIDTH = 1024;
	cam = new Camera(SCREEN_HEIGHT, SCREEN_WIDTH);
	resPath = "";
	Startup();
}

void Game::Startup() {
	//Run only operations related to starting the game. Setup SDL is constructor.
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Failed ot initialize SDL" << std::endl;
		return;
	}

	window = SDL_CreateWindow(gameTitle.c_str(), 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "ERROR: Failed to create Window" << std::endl;
		SDL_Quit();
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << "ERROR: Failed to create Renderer" << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return;
	}
	loadAllAssets();
	running = true;
	run();
}

void Game::loadAllAssets() {
	//Brings all images and their dimensions into system memory, inefficent but acceptable due to scope of game.
	Texture t = Texture("tree.bmp", renderer);
	vTextures.push_back(t); // 0
	Texture grass = Texture("grass.bmp", renderer);
	vTextures.push_back(grass); // 1

	//Load Enemies
	Enemy e1 = Enemy();
	e1.x = 800;
	e1.y = 400;
	SDL_Texture* e1Texture = loadTexture("lava.bmp", renderer);
	e1.tex = e1Texture;
	vEnemies.push_back(e1);
	Enemy e2 = Enemy();

	e2.x = 1400;
	e2.y = 400;
	e2.tex = e1.tex;
	vEnemies.push_back(e2);


	vEnemies.push_back(e2);
	e2.x += 200;
	vEnemies.push_back(e2);
	e2.x += 200;
	vEnemies.push_back(e2);
	e2.x += 200;
	vEnemies.push_back(e2);
	e2.x += 200;
	vEnemies.push_back(e2);
	e2.x += 200;
	vEnemies.push_back(e2);

	//Load Projectiles
	pProj = loadTexture("bProj.bmp", renderer);

	//Link to Tiles
	Tile placeholder1 = Tile(false, -3, "placeholder", 32, 32);
	vTiles.push_back(placeholder1);
	Tile tGrass = Tile(true, 1, "grass", 32, 32);
	vTiles.push_back(tGrass); // 1

	//Load Levels
	Level level1 = Level(150, 24);
	vLevels.push_back(level1); // 0



	for (int i = 0; i < level1.width; i++) {
		vLevels.at(0).setNode(i, (SCREEN_HEIGHT / 32) - 1, 1);
		vLevels.at(0).setNode(i, (SCREEN_HEIGHT / 32) - 2, 1);
	}
	for (int i = 30; i < 75; i++) {
		vLevels.at(0).setNode(i, 18, 1);
	}
}

SDL_Texture* Game::loadTexture(const string &file, SDL_Renderer *ren) {
	//Initialize to nullptr to avoid dangling pointer issues
	SDL_Texture *texture = nullptr;
	//Load the image
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	//If the loading went ok, convert to texture and return the texture
	if (loadedImage != nullptr) {
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
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

void Game::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;

	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(renderer, tex, NULL, &dst);
}
bool Game::CheckDistance(Player p, Enemy e) {
	double distance = ((p.x - e.x) * (p.x - e.x)) + ((p.y - e.y) * (p.y - e.y));
	if (distance == 0) distance = 1;
	distance = sqrt(distance);

	if (distance < 600) return true;
	else return false;
}
bool Game::collides(Enemy e, Projectile p) {

	if ((p.y >= e.y) && (p.y <= e.y + 64)) {
		if (p.x + 15 > e.x) {
			return true;
		}
	}
	return false;
}
bool Game::collides(Player p, Enemy e) {
	if ((p.y >= e.y) && (p.y <= e.y + 64)) {
		if (p.x + 32 > e.x) {
			return true;
		}
	}
	return false;
}
void Game::run() {
	//Houses the primary game loop and runs the update and render methods within the loop
	
	while (running) {

		update();
		render();
		SDL_Delay(1000.0 / 60.0);
	}
}
void Game::GameQuit() {
	SDL_Delay(3000);
	SDL_Quit();
	
	exit(1);
}
void Game::update() {
	//Updates all game objects that require updating
	player.update(vTiles, vLevels);
	int i = 0;
	while (i < vEnemies.size()) {
		if (CheckDistance(player, vEnemies.at(i))) {
			vEnemies.at(i).update(player.x, player.y);
			

			if(collides(player, vEnemies.at(i))) {
				std::cout << "Current Player Health: " << player.health << std::endl;
				if (player.hitTime > 30) {
					player.health -= 10;
					player.hitTime = 0;
					if (player.health <= 0) {
						GameQuit();
					}
				}
				
			}
		}
		i++;
	}
	if (player.shooting) {

		player.shooting = false;
		Projectile p = Projectile(player.x, player.y, player.direction);
		vProj.push_back(p);
		
		
	}
	bool hitEnemy = false;
	int projUpdate = 0;
	while (projUpdate < vProj.size()) {
		vProj.at(projUpdate).update();
		int numE = 0;
		while (numE < vEnemies.size() && !hitEnemy) {
			if (collides(vEnemies.at(numE), vProj.at(projUpdate))) {
				
				vProj.erase(vProj.begin() + projUpdate);
				vEnemies.at(numE).health -= 40;
				hitEnemy = true;
				if (vEnemies.at(numE).health < 0) {
					
					
					vEnemies.erase(vEnemies.begin() + numE);
					numE = vEnemies.size() + 1;
					
					
				}
				
			}
			
			numE++;
		}
		projUpdate++;
	}
	projUpdate = 0;
	while (projUpdate < vProj.size()) {
		
		if (vProj.at(projUpdate).killProjectile()) {
			vProj.erase(vProj.begin() + projUpdate);
		}
		projUpdate++;
	}
	cam->moveCamera(player.x - (SCREEN_HEIGHT / 2), 0);
	if (vEnemies.size() < 1) {
		GameQuit();
	}
}

void Game::render() {
	//Pushes all game objects in need of rendering to the display
	SDL_RenderClear(renderer);

	for (int i = 0; i < vLevels.at(0).height; i++) {
		for (int j = 0; j < vLevels.at(0).width; j++) {
			if (vLevels.at(0).getNode(j, i) >= 0) {
				
				renderTexture(vTextures.at(vTiles.at(1).tileID).tex, renderer, (j * 32) - cam->x, i * 32);
			}
		}
	}
	int projRender = 0;
	while (projRender < vEnemies.size()) {
		renderTexture(vEnemies.at(projRender).tex, renderer, vEnemies.at(projRender).x - cam->x, vEnemies.at(projRender).y);
		projRender++;
	}
	projRender = 0;
	renderTexture(vTextures.at(player.textureID).tex, renderer, player.x - cam->x, player.y);

	while (projRender < vProj.size()) {
		
		renderTexture(pProj, renderer, vProj.at(projRender).x - cam->x, vProj.at(projRender).y);
		projRender++;
	}
	
	SDL_RenderPresent(renderer);
}