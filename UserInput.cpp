#include "UserInput.h"

#include "GLLibs.h"
#include <bitset>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

#define uint unsigned int
#define intptr uintptr_t
#define intptr_vec std::vector<intptr>
#define intptr_vec_uint_umap std::unordered_map<uint, intptr_vec>

typedef void funcT(void); // Used here to simplify the usage and storage of void callback pointers

namespace UserInput {

	static bool has_namespace_been_initialised = false;

	static struct InputState {
		std::bitset<128> keyboard = 0;
		std::bitset<21> special = 0;
	} inputState;

	const bool IsKeyboardKeyDown(const uchar key) {
		return inputState.keyboard[key];
	}
	const bool IsSpecialKeyDown(const SpecialKey key) {
		return inputState.special[key];
	}

	static intptr_vec_uint_umap
		keyboard_down_callback_dict, keyboard_up_callback_dict;

	static intptr_vec_uint_umap
		special_down_callback_dict, special_up_callback_dict;

	inline void RunCallbackFromPointer(const intptr& ptr) {
		funcT* callback = (funcT*)(ptr);
		callback();
	}

	inline void RunCallbacksInPtrVector(const intptr_vec& callback_ptrs) {
		for (uint i = 0; i < callback_ptrs.size(); i++) {			
			RunCallbackFromPointer(callback_ptrs[i]);
		}
	}

	// Keyboard callbacks

	void KeyboardDownCallback(unsigned char key, int mouse_x, int mouse_y) {
		inputState.keyboard.set(key);
		RunCallbacksInPtrVector(keyboard_down_callback_dict[key]);
	}

	void KeyboardUpCallback(unsigned char key, int mouse_x, int mouse_y) {
		inputState.keyboard.reset(key);
		RunCallbacksInPtrVector(keyboard_up_callback_dict[key]);
	}

	// Special callbacks

	void SpecialDownCallback(int key, int mouse_x, int mouse_y) {

		// For some reason all other special keys 
		// after number 12 (being the F12 key) continue from 100 onwards, 
		// so this offsets them back to 13 onwards.
		if (key >= 100) key -= 87;

		inputState.special.set(key);

		RunCallbacksInPtrVector(special_down_callback_dict[key]);
	}

	void SpecialUpCallback(int key, int mouse_x, int mouse_y) {

		if (key >= 100) key -= 87;

		inputState.special.reset(key);
		RunCallbacksInPtrVector(special_up_callback_dict[key]);
	}

	const int Init() {
		if (glutGet(GLUT_INIT_STATE) == 1) {

			glutKeyboardFunc(KeyboardDownCallback);
			glutKeyboardUpFunc(KeyboardUpCallback);

			glutSpecialFunc(SpecialDownCallback);
			glutSpecialUpFunc(SpecialUpCallback);

			has_namespace_been_initialised = true;

			return 0;

		}

		std::cerr << "GLUT must be initialised before initialising UserInput." << std::endl;
		return -1;
	}

	void AddCallback(intptr_vec_uint_umap& dictionary, const uint key, funcT callback) {

		if (dictionary.find(key) == dictionary.end()) {
			dictionary[key] = intptr_vec();
		}

		dictionary[key].push_back((*(intptr*)(&callback))); //  (*(intptr*)(&callback))) retrieves the pointer to the callback.
	}

	void AddKeyboardDownCallback(const uchar key, funcT callback) {
		AddCallback(keyboard_down_callback_dict, key, callback);
	}

	void AddKeyboardUpCallback(const uchar key, funcT callback) {
		AddCallback(keyboard_up_callback_dict, key, callback);
	}

	void AddSpecialDownCallback(const SpecialKey key, funcT callback) {
		AddCallback(special_down_callback_dict, key, callback);
	}

	void AddSpecialUpCallback(const SpecialKey key, funcT callback) {
		AddCallback(special_up_callback_dict, key, callback);
	}

	const bool RemoveCallback(intptr_vec_uint_umap& dictionary, const uint key, funcT callback) {

		if (dictionary.find(key) == dictionary.end()) return false;

		intptr_vec& vect = dictionary[key];
		intptr_vec::iterator it = std::find(vect.begin(), vect.end(), (*(intptr*)(&callback))); //  (*(intptr*)(&callback))) again, retrieves the pointer to the callback.

		if (it == vect.end()) return false;

		vect.erase(it);

		if (vect.size() == 0) {
			delete &dictionary[key];
			dictionary.erase(key);
		}

		return true;
	}

	const bool RemoveKeyboardDownCallback(const uchar key, funcT callback) {
		return RemoveCallback(keyboard_down_callback_dict, key, callback);
	}

	const bool RemoveKeyboardUpCallback(const uchar key, funcT callback) {
		return RemoveCallback(keyboard_up_callback_dict, key, callback);
	}

	const bool RemoveSpecialDownCallback(const SpecialKey key, funcT callback) {
		return RemoveCallback(special_down_callback_dict, key, callback);
	}

	const bool RemoveSpecialUpCallback(const SpecialKey key, funcT callback) {
		return RemoveCallback(special_up_callback_dict, key, callback);
	}

	/// TODO: map each callback to when it's key is down in this script.
}