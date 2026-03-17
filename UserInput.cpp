#include "UserInput.h"

#include "GLLibs.h"
#include <bitset>
#include <unordered_map>

#define bs128 std::bitset<128>
#define bs21 std::bitset<21>
#define uint unsigned int

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
		inputState.keyboard.set(key);
	}

	void KeyboardUpCallback(unsigned char key, int mouse_x, int mouse_y) {
		inputState.keyboard.reset(key);
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

	#define InputCallbackDict std::unordered_map<char, std::vector<void*>>


	static InputCallbackDict
	keyboard_down_callback_dict, special_down_callback_dict,
	keyboard_up_callback_dict,	 special_up_callback_dict;
	
	template<class T_key, class T_value>
	void AddOrUpdateInDictionary(std::unordered_map<T_key, T_value>& dictionary, const T_key key, const T_value value) {
		dictionary.insert_or_assign(key, value);
	}

	template<class T_key, class T_value>
	bool RemoveFromDictionary(std::unordered_map<T_key, T_value>& dictionary, const T_key key, const T_value value) {
		std::unordered_map<T_key, T_value>::iterator it = dictionary.find(key);
		if (it == dictionary.end())
			return false;

		dictionary.erase(it);
		return true;
	}

	void AddKeyboardDownCallback(char key, void* callback) {
		keyboard_down_callback_dict[key].push_back(callback);
	}

	void AddSpecialDownCallback(int key, void* callback) {
		special_down_callback_dict[key].push_back(callback);
	}

	void AddKeyboardUpCallback(char key, void* callback) {
		keyboard_up_callback_dict[key].push_back(callback);
	}

	void AddSpecialUpCallback(int key, void* callback) {
		special_up_callback_dict[key].push_back(callback);
	}

	bool RemoveKeyboardDownCallback(char key, void* callback) {
		auto& vect = keyboard_down_callback_dict[key];
		auto it = std::find(vect.begin(), vect.end(), callback);

		if (it == vect.end()) {
			return false;
		}

		vect.erase(it);
		return true;
	}

	bool RemoveSpecialDownCallback(int key, void* callback) {
		auto& vect = special_down_callback_dict[key];
		auto it = std::find(vect.begin(), vect.end(), callback);

		if (it == vect.end()) {
			return false;
		}

		vect.erase(it);
		return true;
	}

	bool RemoveKeyboardUpCallback(char key, void* callback) {
		auto& vect = keyboard_up_callback_dict[key];
		auto it = std::find(vect.begin(), vect.end(), callback);

		if (it == vect.end()) {
			return false;
		}

		vect.erase(it);
		return true;
	}

	bool RemoveSpecialUpCallback(int key, void* callback) {
		auto& vect = special_up_callback_dict[key];
		auto it = std::find(vect.begin(), vect.end(), callback);

		if (it == vect.end()) {
			return false;
		}

		vect.erase(it);
		return true;
	}

	/// TODO: map each callback to when it's key is down in this script.
}