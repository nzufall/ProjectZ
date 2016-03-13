#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <SDL.h>
class Input {
public:
	Input();
	void ClearOldStates();
	void keyPressed(const SDL_Event& event);
	void keyReleased(const SDL_Event& event);
	bool keyState(SDL_Scancode key);
private:
	std::map<int, bool> keyboard; 
};
#endif // !INPUT_H
