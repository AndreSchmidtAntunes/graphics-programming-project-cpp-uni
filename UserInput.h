#pragma once

#include <functional>
#define uchar unsigned char
#define callbackfunc_ptr void (*callback)(void)

typedef void funcT(void);
//#define callbackfunc_ptr funcT callback
namespace UserInput {	

	enum SpecialKey : int 
	{
		F1 = 1, 
		F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		
		LEFT = 13,
		UP, RIGHT, DOWN, PAGE_UP, PAGE_DOWN, HOME, END, INSERT
	};

	const void Init();

	const bool IsKeyboardKeyDown(const uchar key);
	const bool IsSpecialKeyDown(const SpecialKey key);

	// Keyboard input callbacks

	void AddKeyboardDownCallback(const uchar key, callbackfunc_ptr);
	void AddKeyboardUpCallback(const uchar key, callbackfunc_ptr);

	const bool RemoveKeyboardDownCallback(const uchar key, callbackfunc_ptr);
	const bool RemoveKeyboardUpCallback(const uchar key, callbackfunc_ptr);

	// Special input callbacks

	void AddSpecialDownCallback(const int key, callbackfunc_ptr);
	void AddSpecialUpCallback(const int key, callbackfunc_ptr);

	const bool RemoveSpecialDownCallback(const int key, callbackfunc_ptr);
	const bool RemoveSpecialUpCallback(const int key, callbackfunc_ptr);
}