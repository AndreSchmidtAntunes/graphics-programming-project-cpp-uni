#pragma once

#define uchar unsigned char
#define voidcallback void (*callback)(void)

namespace UserInput {	

	const enum SpecialKey : int 
	{
		F1 = 1, 
		F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		
		LEFT = 13,
		UP, RIGHT, DOWN, PAGE_UP, PAGE_DOWN, HOME, END, INSERT
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
}