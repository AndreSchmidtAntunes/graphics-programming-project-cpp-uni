#pragma once

namespace UserInput {	

	const enum SpecialKey : int 
	{
		F1 = 0, 
		F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		
		LEFT = 12,
		UP, RIGHT, DOWN, PAGE_UP, PAGE_DOWN, HOME, END, INSERT,

		LEFT_SHIFT = 24,
		RIGHT_SHIFT, LEFT_CTRL, RIGHT_CTRL, LEFT_ALT, RIGHT_ALT,

	};

	const int Init();

	const bool IsKeyboardKeyDown(const unsigned char key);
	const bool IsSpecialKeyDown(const SpecialKey key);

	// Keyboard inputs

	void AddKeyboardDownCallback(const unsigned char key, void (*callback)(void));
	void AddKeyboardUpCallback(const unsigned char key, void (*callback)(void));

	const bool RemoveKeyboardDownCallback(const unsigned char key, void (*callback)(void));
	const bool RemoveKeyboardUpCallback(const unsigned char key, void (*callback)(void));

	// Special inputs

	void AddSpecialDownCallback(const SpecialKey key, void (*callback)(void));
	void AddSpecialUpCallback(const SpecialKey key, void (*callback)(void));

	const bool RemoveSpecialDownCallback(const SpecialKey key, void (*callback)(void));
	const bool RemoveSpecialUpCallback(const SpecialKey key, void (*callback)(void));

	void AddKeyboardActiveCallback(const unsigned char key, void (*callback)(void));
	const bool RemoveKeyboardActiveCallback(const unsigned char key, void (*callback)(void));

	void AddSpecialActiveCallback(const SpecialKey key, void (*callback)(void));
	const bool RemoveSpecialActiveCallback(const SpecialKey key, void (*callback)(void));

	void UserInputActiveCallbacks();
}