#pragma once

#define uchar unsigned char
#define voidcallback void (*callback)(void)

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

	const bool IsKeyboardKeyDown(const uchar key);
	const bool IsSpecialKeyDown(const SpecialKey key);

	// Keyboard inputs

	void AddKeyboardDownCallback(const uchar key, voidcallback);
	void AddKeyboardUpCallback(const uchar key, voidcallback);

	const bool RemoveKeyboardDownCallback(const uchar key, voidcallback);
	const bool RemoveKeyboardUpCallback(const uchar key, voidcallback);

	// Special inputs

	void AddSpecialDownCallback(const SpecialKey key, voidcallback);
	void AddSpecialUpCallback(const SpecialKey key, voidcallback);

	const bool RemoveSpecialDownCallback(const SpecialKey key, voidcallback);
	const bool RemoveSpecialUpCallback(const SpecialKey key, voidcallback);

	void AddKeyboardActiveCallback(const uchar key, voidcallback);
	const bool RemoveKeyboardActiveCallback(const uchar key, voidcallback);

	void AddSpecialActiveCallback(const SpecialKey key, voidcallback);
	const bool RemoveSpecialActiveCallback(const SpecialKey key, voidcallback);

	void UserInputActiveCallbacks();
}