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
	Texture t = Texture("hello.bmp", renderer);
	vTextures.push_back(t); // 0
	Texture grass = Texture("grass.bmp", renderer);
	vTextures.push_back(grass); // 1


	//Link to Tiles
	Tile placeholder1 = Tile(false, -3, "placeholder", 32, 32);
	vTiles.push_back(placeholder1);
	Tile tGrass = Tile(true, 1, "grass", 32, 32);
	vTiles.push_back(tGrass); // 1

	//Load Levels
	Level level1 = Level(150, 24);
	vLevels.push_back(level1); // 0

	vLevels.at(0).setNode(0, 20, 1);
	vLevels.at(0).setNode(1, 20, 1);
	vLevels.at(0).setNode(2, 20, 1);
	vLevels.at(0).setNode(3, 20, 1);
	vLevels.at(0).setNode(4, 20, 1);
	vLevels.at(0).setNode(5, 20, 1);
	vLevels.at(0).setNode(6, 20, 1);
	vLevels.at(0).setNode(7, 20, 1);
	vLevels.at(0).setNode(8, 20, 1);
	vLevels.at(0).setNode(9, 20, 1);
	vLevels.at(0).setNode(0, 21, 1);
	vLevels.at(0).setNode(1, 21, 1);
	vLevels.at(0).setNode(2, 21, 1);
	vLevels.at(0).setNode(3, 21, 1);
	vLevels.at(0).setNode(4, 21, 1);
	vLevels.at(0).setNode(5, 21, 1);
	vLevels.at(0).setNode(6, 21, 1);
	vLevels.at(0).setNode(7, 21, 1);
	vLevels.at(0).setNode(8, 21, 1);
	vLevels.at(0).setNode(9, 21, 1);
	vLevels.at(0).setNode(9, 19, 1);
	vLevels.at(0).setNode(9, 18, 1);
	vLevels.at(0).setNode(9, 17, 1);
	vLevels.at(0).setNode(8, 17, 1);
	vLevels.at(0).setNode(7, 17, 1);
	vLevels.at(0).setNode(9, 16, 1);
	vLevels.at(0).setNode(9, 15, 1);
	for (int i = 10; i < 30; i++) {
		vLevels.at(0).setNode(i, 15, 1);
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

void Game::run() {
	//Houses the primary game loop and runs the update and render methods within the loop
	
	while (running) {

		update();
		render();
		SDL_Delay(1000.0 / 60.0);
	}
}

void Game::update() {
	//Updates all game objects that require updating
	player.update(vTiles, vLevels);
	cam->moveCamera(player.x - (SCREEN_HEIGHT / 2), 0);
	std::cout << "X: " << cam->x + SCREEN_WIDTH<< ", Y: " << cam->y << std::endl;
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
	renderTexture(vTextures.at(player.textureID).tex, renderer, player.x - cam->x, player.y);

	SDL_RenderPresent(renderer);
}