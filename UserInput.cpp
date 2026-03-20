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

// This Typedef is used here to simplify the usage and storage of void callback pointers.
// It is interchangeable with the type: void (*)(void)
typedef void funcT(void); 

namespace UserInput {

	static bool has_namespace_been_initialised = false;

	static struct InputState {
		std::bitset<128> keyboard = 0;
		std::bitset<30> special = 0;
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

		key--; // move the key to be in the range of index 0 onwards.

		inputState.special.set(key);

		RunCallbacksInPtrVector(special_down_callback_dict[key]);
	}

	void SpecialUpCallback(int key, int mouse_x, int mouse_y) {

		if (key >= 100) key -= 87;

		key--;

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

	/// <summary>
	/// Stores the given void callback into the array paired with the given key inside of the given dictionary.<br/>
	/// When a void callback <c>Foo()</c> is given with the key being <c>a</c>, 
	/// a pointer to <c>Foo()</c> would be pushed to the rear of an array in the given dictionary at the key <c>a</c>. 
	/// </summary>
	/// <param name="dictionary">The dictionary to store the callback pointer into.</param>
	/// <param name="key">The key to the array you want to append the callback to.</param>
	/// <param name="callback">The callback pointer you wish to add.</param>
	void AddCallback(intptr_vec_uint_umap& dictionary, const uint key, funcT* callback) {

		if (dictionary.find(key) == dictionary.end()) {
			dictionary[key] = intptr_vec();
		}

		dictionary[key].push_back((*(intptr*)(&callback))); 
	}

	/// <summary>
	/// Stores a reference to the given callback pointer, so that the callback is ran whenever the given key is pressed down.
	/// </summary>
	/// <param name="key">The keyboard key which fires the callback.</param>
	/// <param name="">The void callback which runs when the key is pressed down.</param>
	void AddKeyboardDownCallback(const uchar key, voidcallback) {
		AddCallback(keyboard_down_callback_dict, key, callback);
	}

	/// <summary>
	/// Stores a reference to the given callback pointer, so that the callback is ran whenever the given key is released.
	/// </summary>
	/// <param name="key">The keyboard key which fires the callback.</param>
	/// <param name="">The void callback which runs when the key is released.</param>
	void AddKeyboardUpCallback(const uchar key, voidcallback) {
		AddCallback(keyboard_up_callback_dict, key, callback);
	}

	/// <summary>
	/// Stores a reference to the given callback pointer, so that the callback is ran whenever the given key is pressed down.
	/// </summary>
	/// <param name="key">The special keyboard key which fires the callback.</param>
	/// <param name="">The void callback which runs when the key is pressed down.</param>
	void AddSpecialDownCallback(const SpecialKey key, voidcallback) {
		AddCallback(special_down_callback_dict, key, callback);
	}

	/// <summary>
	/// Stores a reference to the given callback pointer, so that the callback is ran whenever the given key is released.
	/// </summary>
	/// <param name="key">The special keyboard key which fires the callback.</param>
	/// <param name="">The void callback which runs when the key is released.</param>
	void AddSpecialUpCallback(const SpecialKey key, voidcallback) {
		AddCallback(special_up_callback_dict, key, callback);
	}

	/// <summary>
	/// Pops a stored reference to the given void callback from the array paired with the given key inside of the given dictionary.<br/>
	/// When a void callback <c>Foo()</c> is given with the key being <c>a</c>, 
	/// a pointer to <c>Foo()</c> would attempt to be removed from an array in the given dictionary at the key <c>a</c>. 
	/// </summary>
	/// <param name="dictionary">The dictionary holding the callback pointer to remove.</param>
	/// <param name="key">The key to the array you want to pop a reference of the callback from.</param>
	/// <param name="callback">The callback pointer you wish to pop from the array. </param>
	const bool RemoveCallback(intptr_vec_uint_umap& dictionary, const uint key, funcT* callback) {

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

	/// <summary>
	/// Removes a reference of the given callback pointer, so that it will no longer be ran when the given keyboard key is pressed down.
	/// </summary>
	/// <param name="key">The keyboard key which is currently firing the callback.</param>
	/// <param name="">The void callback to be removed from the fire order.</param>
	const bool RemoveKeyboardDownCallback(const uchar key, voidcallback) {
		return RemoveCallback(keyboard_down_callback_dict, key, callback);
	}

	/// <summary>
	/// Removes a reference of the given callback pointer, so that it will no longer be ran when the given keyboard key is released.
	/// </summary>
	/// <param name="key">The keyboard key which is currently firing the callback.</param>
	/// <param name="">The void callback to be removed from the fire order.</param>
	const bool RemoveKeyboardUpCallback(const uchar key, voidcallback) {
		return RemoveCallback(keyboard_up_callback_dict, key, callback);
	}

	/// <summary>
	/// Removes a reference of the given callback pointer, so that it will no longer be ran when the given special keyboard key is pressed down.
	/// </summary>
	/// <param name="key">The special keyboard key which is currently firing the callback.</param>
	/// <param name="">The void callback to be removed from the fire order.</param>
	const bool RemoveSpecialDownCallback(const SpecialKey key, voidcallback) {
		return RemoveCallback(special_down_callback_dict, key, callback);
	}

	/// <summary>
	/// Removes a reference of the given callback pointer, so that it will no longer be ran when the given special keyboard key is released.
	/// </summary>
	/// <param name="key">The special keyboard key which is currently firing the callback.</param>
	/// <param name="">The void callback to be removed from the fire order.</param>
	const bool RemoveSpecialUpCallback(const SpecialKey key, voidcallback) {
		return RemoveCallback(special_up_callback_dict, key, callback);
	}
}