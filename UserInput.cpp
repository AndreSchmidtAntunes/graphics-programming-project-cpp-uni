#include "UserInput.h"

#include <bitset>
#include "GLLibs.h"

#include <iostream> /// DELETE THIS LTR

#define bs128 std::bitset<128>
#define bs21 std::bitset<21>

namespace UserInput {

	static struct InputState {
		bs128 keyboard = 0;
		bs21 special = 0;
	} inputState;

	const inline bool IsKeyboardKeyDown(char key) {
		return inputState.keyboard[key];
	}
	const inline bool IsSpecialKeyDown(SpecialKey key) {
		return inputState.keyboard[key];
	}

	// Keyboard callbacks

	void KeyboardCallback(unsigned char key, int mouse_x, int mouse_y) {
		inputState.keyboard.set(key);										std::cout << key;
	}

	void KeyboardUpCallback(unsigned char key, int mouse_x, int mouse_y) {
		inputState.keyboard.reset(key);										std::cout << key;
	}

	// Special callbacks

	void SpecialCallback(int key, int mouse_x, int mouse_y) {

		// For some reason all other special keys 
		// after number 12 (being the F12 key) continue from 100 onwards, 
		// so this offsets them back to 13 onwards.
		if (key >= 100) key -= 87;

		inputState.special.set(key);
	}

	void SpecialUpCallback(int key, int mouse_x, int mouse_y) {

		if (key >= 100) key -= 87;

		inputState.special.reset(key);
	}

	const void Init() {
		glutKeyboardFunc(KeyboardCallback);
		glutKeyboardUpFunc(KeyboardUpCallback);

		glutSpecialFunc(SpecialCallback);
		glutSpecialUpFunc(SpecialUpCallback);
	}
}