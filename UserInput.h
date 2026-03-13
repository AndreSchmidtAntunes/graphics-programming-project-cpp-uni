#pragma once

namespace UserInput {	

	enum SpecialKey : int 
	{
		F1 = 1, 
		F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		
		LEFT = 13,
		UP, RIGHT, DOWN, PAGE_UP, PAGE_DOWN, HOME, END, INSERT
	};

	const void Init();

	const inline bool IsKeyboardKeyDown(char key);

	const inline bool IsSpecialKeyDown(SpecialKey key);
}