#include "Input.h"

Input::Input() {

}
void Input::ClearOldStates() {
	keyboard.clear();
}
void Input::keyPressed(const SDL_Event& event) {
	keyboard[event.key.keysym.scancode] = true;
}
void Input::keyReleased(const SDL_Event& event) {
	keyboard[event.key.keysym.scancode] = false;
}
bool Input::keyState(SDL_Scancode key) {
	return keyboard[key];
}