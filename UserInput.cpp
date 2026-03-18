#include "UserInput.h"

#include "GLLibs.h"
#include <bitset>
#include <unordered_map>

#define bs128 std::bitset<128>
#define bs21 std::bitset<21>

#define uint unsigned int
#define intptr uintptr_t
#define intptr_vec std::vector<intptr>
#define intptr_vec_uint_umap std::unordered_map<uint, intptr_vec>

namespace UserInput {

	static struct InputState {
		bs128 keyboard = 0;
		bs21 special = 0;
	} inputState;

	const bool IsKeyboardKeyDown(const uchar key) {
		return inputState.keyboard[key];
	}
	const bool IsSpecialKeyDown(const SpecialKey key) {
		return inputState.keyboard[key];
	}

	static intptr_vec_uint_umap
		keyboard_down_callback_dict, keyboard_up_callback_dict;

	static intptr_vec_uint_umap
		special_down_callback_dict, special_up_callback_dict;

	void RunCallbackFromPointer(const intptr& ptr) {
		funcT* f = (funcT*)(ptr);
		f();
	}

	void RunCallbacksInPtrVector(const intptr_vec& callback_ptrs) {
		for (uint i = 0; i < callback_ptrs.size(); i++) {
			// loop through each callback for the given key;
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

	const void Init() {
		glutKeyboardFunc(KeyboardDownCallback);
		glutKeyboardUpFunc(KeyboardUpCallback);

		glutSpecialFunc(SpecialDownCallback);
		glutSpecialUpFunc(SpecialUpCallback);		
	}

	void AddCallback(intptr_vec_uint_umap& dictionary, const uint key, callbackfunc_ptr) {

		if (dictionary.find(key) == dictionary.end()) {
			dictionary[key] = intptr_vec();
		}

		dictionary[key].push_back(*((intptr*)(&callback)));
	}

	void AddKeyboardDownCallback(const uchar key, callbackfunc_ptr) {
		AddCallback(keyboard_down_callback_dict, key, callback);
	}

	void AddKeyboardUpCallback(const uchar key, callbackfunc_ptr) {
		AddCallback(keyboard_up_callback_dict, key, callback);
	}

	void AddSpecialDownCallback(const int key, callbackfunc_ptr) {
		AddCallback(special_down_callback_dict, key, callback);
	}

	void AddSpecialUpCallback(const int key, callbackfunc_ptr) {
		AddCallback(special_up_callback_dict, key, callback);
	}

	const bool RemoveCallback(intptr_vec_uint_umap& dictionary, const uint key, callbackfunc_ptr) {

		if (dictionary.find(key) == dictionary.end()) return false;

		auto& vect = dictionary[key];
		auto it = std::find(vect.begin(), vect.end(), *((intptr*)(&callback)));

		if (it == vect.end()) return false;

		vect.erase(it);

		if (vect.size() == 0) {
			delete &dictionary[key];
			dictionary.erase(key);
		}

		return true;
	}

	const bool RemoveKeyboardDownCallback(const uchar key, callbackfunc_ptr) {
		return RemoveCallback(keyboard_down_callback_dict, key, callback);
	}

	const bool RemoveKeyboardUpCallback(const uchar key, callbackfunc_ptr) {
		return RemoveCallback(keyboard_up_callback_dict, key, callback);
	}

	const bool RemoveSpecialDownCallback(const int key, callbackfunc_ptr) {
		return RemoveCallback(special_down_callback_dict, key, callback);
	}

	const bool RemoveSpecialUpCallback(const int key, callbackfunc_ptr) {
		return RemoveCallback(special_up_callback_dict, key, callback);
	}

	/// TODO: map each callback to when it's key is down in this script.
}