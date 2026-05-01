#pragma once

#include <iostream>

#include "Vector2.h"

namespace UserInput {	

	const enum SpecialInputs : int 
	{
		F1 = 0, 
		F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		
		LEFT = 12,
		UP, RIGHT, DOWN, PAGE_UP, PAGE_DOWN, HOME, END, INSERT,

		LEFT_SHIFT = 24,
		RIGHT_SHIFT, LEFT_CTRL, RIGHT_CTRL, LEFT_ALT, RIGHT_ALT,

	};

	enum MouseInputs : size_t { LMB, MMB, RMB };

	const Vector2I& getMousePos();
	const Vector2I getMouseDelta();

	const int Init();

	const bool IsKeyboardKeyDown(const unsigned char key);
	const bool IsSpecialKeyDown(const SpecialInputs key);
	const bool IsMouseDown(const MouseInputs key);

	// Keyboard inputs

	void AddKeyboardDownCallback(const unsigned char key, void (*callback)(void));
	void AddKeyboardUpCallback(const unsigned char key, void (*callback)(void));

	const bool RemoveKeyboardDownCallback(const unsigned char key, void (*callback)(void));
	const bool RemoveKeyboardUpCallback(const unsigned char key, void (*callback)(void));

	// Special inputs

	void AddSpecialDownCallback(const SpecialInputs key, void (*callback)(void));
	void AddSpecialUpCallback(const SpecialInputs key, void (*callback)(void));

	const bool RemoveSpecialDownCallback(const SpecialInputs key, void (*callback)(void));
	const bool RemoveSpecialUpCallback(const SpecialInputs key, void (*callback)(void));

	void AddKeyboardActiveCallback(const unsigned char key, void (*callback)(void));
	const bool RemoveKeyboardActiveCallback(const unsigned char key, void (*callback)(void));

	void AddSpecialActiveCallback(const SpecialInputs key, void (*callback)(void));
	const bool RemoveSpecialActiveCallback(const SpecialInputs key, void (*callback)(void));

	// Mouse inputs

	void AddMouseDownCallback(const MouseInputs input, void (*callback)(void));
	const bool RemoveMouseDownCallback(const MouseInputs input, void (*callback)(void));

	void AddMouseUpCallback(const MouseInputs input, void (*callback)(void));
	const bool RemoveMouseUpCallback(const MouseInputs input, void (*callback)(void));

	void AddMouseMoveCallback(void (*callback)(void));
	const bool RemoveMouseMoveCallback(void (*callback)(void));

	void AddMouseDragCallback(void (*callback)(void));
	const bool RemoveMouseDragCallback(void (*callback)(void));

	void RunAllActiveCallbacks();
}