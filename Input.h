#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <SDL.h>
class Input {
public:
	/**
	* Constructor
	*/
	Input();
	/**
	* Used to clear out map
	*/
	void ClearOldStates();
	/**
	* marks keys as pressed
	* @param event the triggering SDL_Event is set to true
	*/
	void keyPressed(const SDL_Event& event);
	/**
	* Marks keys as released
	* @param event the triggered SDL_Event is set to false;
	*/
	void keyReleased(const SDL_Event& event);
	/**
	* Returns the value for a certain key
	* @param key the key state being requested that corresponds to the key code
	*/
	bool keyState(SDL_Scancode key);
private:
	std::map<int, bool> keyboard; 
};
#endif // !INPUT_H
