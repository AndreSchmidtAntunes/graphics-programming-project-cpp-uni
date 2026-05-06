#include "UserInput.h"

#include "GLLibs.h"
#include <bitset>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include "imguiLibs.h"

#define intptr uintptr_t
#define intptr_vec std::vector<intptr>
#define intptr_vec_uint_umap std::unordered_map<size_t, intptr_vec>

// This Typedef is used here to simplify the usage and storage of void callback pointers.
// It is interchangeable with the type: void (*)(void)
typedef void funcT(void);

namespace UserInput {

	static bool has_namespace_been_initialised = false;

	bool enabled = false; // If Input events should fire

	static struct InputState {
		std::bitset<128> keyboard = 0;
		std::bitset<32> special = 0;
		std::bitset<3> mouse = 0;
	} inputState;

	const bool IsKeyboardKeyDown(const unsigned char key) {
		return inputState.keyboard[key];
	}

	const bool IsSpecialKeyDown(const SpecialInputs key) {
		return inputState.special[key];
	}

	const bool IsMouseDown(const MouseInputs key) {
		return inputState.mouse[key];
	}

	static intptr_vec_uint_umap
		keyboard_down_callback_dict, keyboard_active_callback_dict, keyboard_up_callback_dict;

	static intptr_vec_uint_umap
		special_down_callback_dict, special_active_callback_dict, special_up_callback_dict;

	static intptr_vec_uint_umap
		mouse_down_callback_dict, mouse_active_callback_dict, mouse_up_callback_dict;
	static intptr_vec mouse_drag_callbacks, mouse_move_callbacks;

	inline void RunCallbackFromPointer(const intptr& ptr) {
		funcT* callback = (funcT*)(ptr);
		callback();
	}

	inline void RunCallbacksInPtrVector(const intptr_vec& callback_ptrs) {
		for (size_t i = 0; i < callback_ptrs.size(); i++) {			
			RunCallbackFromPointer(callback_ptrs[i]);
		}
	}

	Vector2I _oldMousePos;
	Vector2I _mousePos;

	const Vector2I& getMousePos() {
		return _mousePos;
	}

	const Vector2I getMouseDelta() {
		return _mousePos - _oldMousePos;
	}

	// Keyboard callbacks

	void KeyboardDownCallback(unsigned char key, int mouse_x, int mouse_y) {

		if (!enabled) return;

		ImGui_ImplGLUT_KeyboardUpFunc(key, mouse_x, mouse_y);
		ImGuiIO& io = ImGui::GetIO();
		if (io.WantCaptureKeyboard) return;

		if (inputState.keyboard[key] == 0) {
			RunCallbacksInPtrVector(keyboard_down_callback_dict[key]);
			inputState.keyboard.set(key);
		}
	}

	void KeyboardUpCallback(unsigned char key, int mouse_x, int mouse_y) {

		if (!enabled) return;

		ImGui_ImplGLUT_KeyboardFunc(key, mouse_x, mouse_y);
		ImGuiIO& io = ImGui::GetIO();
		if (io.WantCaptureKeyboard) return;

		if (inputState.keyboard[key] == 1) {
			RunCallbacksInPtrVector(keyboard_up_callback_dict[key]);
			inputState.keyboard.reset(key);
		}	
	}

	// Special callbacks
	void SpecialDownCallback(int key, int mouse_x, int mouse_y) {

		if (!enabled) return;

		ImGui_ImplGLUT_SpecialFunc(key, mouse_x, mouse_y);
		ImGuiIO& io = ImGui::GetIO();
		if (io.WantCaptureKeyboard) return;

		// For some reason all other special keys 
		// after number 12 (being the F12 key) continue from 100 onwards, 
		// so this offsets them back to 13 onwards.
		if (key >= 100) key -= 87;

		key--; // move the key to be in the range of index 0 onwards.

		if (inputState.special[key] == 0) {
			RunCallbacksInPtrVector(special_down_callback_dict[key]);
			inputState.special.set(key);
		}
	}

	void SpecialUpCallback(int key, int mouse_x, int mouse_y) {

		if (!enabled) return;

		ImGui_ImplGLUT_SpecialUpFunc(key, mouse_x, mouse_y);
		ImGuiIO& io = ImGui::GetIO();
		if (io.WantCaptureKeyboard) return;

		if (key >= 100) key -= 87;

		key--;

		if (inputState.special[key] == 1) {
			RunCallbacksInPtrVector(special_up_callback_dict[key]);
			inputState.special.reset(key);
		}
	}

	void MouseCallback(int button, int state, int mouse_x, int mouse_y) {

		if (!enabled) return;

		ImGui_ImplGLUT_MouseFunc(button, state, mouse_x, mouse_y);
		ImGuiIO& io = ImGui::GetIO();
		if (io.WantCaptureMouse) return;

		size_t state_index;
		switch (button) {
		case GLUT_LEFT_BUTTON: state_index = 0; break;
		case GLUT_MIDDLE_BUTTON: state_index = 1; break;
		case GLUT_RIGHT_BUTTON: state_index = 2; break;
		default:return;
		}

		bool is_down = !state; // mouse state has UP as 1 and DOWN as 0, so invert it

		if (inputState.mouse[state_index] != is_down) { // run update of mouse input state if it has changed
			
			auto& dict = is_down ? mouse_down_callback_dict : mouse_up_callback_dict;

			RunCallbacksInPtrVector(dict[state_index]);
			inputState.mouse.set(state_index, is_down);
		}
	}

	void MouseDragCallback(int mouse_x, int mouse_y) {

		if (!enabled) return;

		ImGui_ImplGLUT_MotionFunc(mouse_x, mouse_y);
		ImGuiIO& io = ImGui::GetIO();

		_mousePos.x = mouse_x;
		_mousePos.y = mouse_y;
		if (!io.WantCaptureMouse) RunCallbacksInPtrVector(mouse_drag_callbacks);
		_oldMousePos = _mousePos;
	}

	void MouseMoveCallback(int mouse_x, int mouse_y) {

		if (!enabled) return;

		ImGui_ImplGLUT_MotionFunc(mouse_x, mouse_y);
		ImGuiIO& io = ImGui::GetIO();

		_mousePos.x = mouse_x;
		_mousePos.y = mouse_y;
		if (! io.WantCaptureMouse) RunCallbacksInPtrVector(mouse_move_callbacks);
		_oldMousePos = _mousePos;
	}

	const int Init(bool enable_emediatly) {
		if (glutGet(GLUT_INIT_STATE) == 1 && !has_namespace_been_initialised) {

			glutKeyboardFunc(KeyboardDownCallback);
			glutKeyboardUpFunc(KeyboardUpCallback);

			glutSpecialFunc(SpecialDownCallback);
			glutSpecialUpFunc(SpecialUpCallback);

			glutMouseFunc(MouseCallback);

			glutMotionFunc(MouseDragCallback);
			glutPassiveMotionFunc(MouseMoveCallback);

			has_namespace_been_initialised = true;
			enabled = enable_emediatly;
			
			return 0;

		}

		std::cerr << "GLUT must be initialised before initialising UserInput." << std::endl;
		return -1;
	}


	void Enable() {
		enabled = true;
	}

	void Disable() {
		enabled = false;
		inputState.keyboard = 0;
		inputState.special = 0;
		inputState.mouse = 0;
	}

	/// <summary>
	/// Stores the given void callback into the array paired with the given key inside of the given dictionary.<br/>
	/// When a void callback <c>Foo()</c> is given with the key being <c>a</c>, 
	/// a pointer to <c>Foo()</c> would be pushed to the rear of an array in the given dictionary at the key <c>a</c>. 
	/// </summary>
	/// <param name="dictionary">The dictionary to store the callback pointer into.</param>
	/// <param name="key">The key to the array you want to append the callback to.</param>
	/// <param name="callback">The callback pointer you wish to add.</param>
	void AddCallback(intptr_vec_uint_umap& dictionary, const size_t key, funcT* callback) {

		if (dictionary.find(key) == dictionary.end()) {
			dictionary[key] = intptr_vec();
		}

		dictionary[key].push_back((*(intptr*)(&callback))); 
	}

	/// <summary>
	/// Pops a stored reference to the given void callback from the array paired with the given key inside of the given dictionary.<br/>
	/// When a void callback <c>Foo()</c> is given with the key being <c>a</c>, 
	/// a pointer to <c>Foo()</c> would attempt to be removed from an array in the given dictionary at the key <c>a</c>. 
	/// </summary>
	/// <param name="dictionary">The dictionary holding the callback pointer to remove.</param>
	/// <param name="key">The key to the array you want to pop a reference of the callback from.</param>
	/// <param name="callback">The callback pointer you wish to pop from the array. </param>
	const bool RemoveCallback(intptr_vec_uint_umap& dictionary, const size_t key, funcT* callback) {

		if (dictionary.find(key) == dictionary.end()) return false;

		intptr_vec& vect = dictionary[key];
		intptr_vec::iterator it = std::find(vect.begin(), vect.end(), (*(intptr*)(&callback))); //  (*(intptr*)(&callback))) again, retrieves the pointer to the callback.

		if (it == vect.end()) return false;

		vect.erase(it);

		if (vect.size() == 0) {
			delete& dictionary[key];
			dictionary.erase(key);
		}

		return true;
	}

	// --- Keyboard --- //

	/// <summary>
	/// Stores a reference to the given callback pointer, so that the callback is ran whenever the given key is pressed down.
	/// </summary>
	/// <param name="key">The keyboard key which fires the callback.</param>
	/// <param name="">The void callback which runs when the key is pressed down.</param>
	void AddKeyboardDownCallback(const unsigned char key, void (*callback)(void)) {
		AddCallback(keyboard_down_callback_dict, key, callback);
	}

	/// <summary>
	/// Stores a reference to the given callback pointer, so that the callback is ran whenever the given key is released.
	/// </summary>
	/// <param name="key">The keyboard key which fires the callback.</param>
	/// <param name="">The void callback which runs when the key is released.</param>
	void AddKeyboardUpCallback(const unsigned char key, void (*callback)(void)) {
		AddCallback(keyboard_up_callback_dict, key, callback);
	}

	/// <summary>
	/// Removes a reference of the given callback pointer, so that it will no longer be ran when the given keyboard key is pressed down.
	/// </summary>
	/// <param name="key">The keyboard key which is currently firing the callback.</param>
	/// <param name="">The void callback to be removed from the fire order.</param>
	const bool RemoveKeyboardDownCallback(const unsigned char key, void (*callback)(void)) {
		return RemoveCallback(keyboard_down_callback_dict, key, callback);
	}

	/// <summary>
	/// Removes a reference of the given callback pointer, so that it will no longer be ran when the given keyboard key is released.
	/// </summary>
	/// <param name="key">The keyboard key which is currently firing the callback.</param>
	/// <param name="">The void callback to be removed from the fire order.</param>
	const bool RemoveKeyboardUpCallback(const unsigned char key, void (*callback)(void)) {
		return RemoveCallback(keyboard_up_callback_dict, key, callback);
	}

	void AddKeyboardActiveCallback(const unsigned char key, void (*callback)(void)) {
		AddCallback(keyboard_active_callback_dict, key, callback);
	}

	const bool RemoveKeyboardActiveCallback(const unsigned char key, void (*callback)(void)) {
		return RemoveCallback(keyboard_active_callback_dict, key, callback);
	}

	// --- Special --- //

	/// <summary>
	/// Stores a reference to the given callback pointer, so that the callback is ran whenever the given key is pressed down.
	/// </summary>
	/// <param name="key">The special keyboard key which fires the callback.</param>
	/// <param name="">The void callback which runs when the key is pressed down.</param>
	void AddSpecialDownCallback(const SpecialInputs key, void (*callback)(void)) {
		AddCallback(special_down_callback_dict, key, callback);
	}

	/// <summary>
	/// Stores a reference to the given callback pointer, so that the callback is ran whenever the given key is released.
	/// </summary>
	/// <param name="key">The special keyboard key which fires the callback.</param>
	/// <param name="">The void callback which runs when the key is released.</param>
	void AddSpecialUpCallback(const SpecialInputs key, void (*callback)(void)) {
		AddCallback(special_up_callback_dict, key, callback);
	}

	/// <summary>
	/// Removes a reference of the given callback pointer, so that it will no longer be ran when the given special keyboard key is pressed down.
	/// </summary>
	/// <param name="key">The special keyboard key which is currently firing the callback.</param>
	/// <param name="">The void callback to be removed from the fire order.</param>
	const bool RemoveSpecialDownCallback(const SpecialInputs key, void (*callback)(void)) {
		return RemoveCallback(special_down_callback_dict, key, callback);
	}

	/// <summary>
	/// Removes a reference of the given callback pointer, so that it will no longer be ran when the given special keyboard key is released.
	/// </summary>
	/// <param name="key">The special keyboard key which is currently firing the callback.</param>
	/// <param name="">The void callback to be removed from the fire order.</param>
	const bool RemoveSpecialUpCallback(const SpecialInputs key, void (*callback)(void)) {
		return RemoveCallback(special_up_callback_dict, key, callback);
	}

	void AddSpecialActiveCallback(const SpecialInputs key, void (*callback)(void)) {
		AddCallback(special_active_callback_dict, key, callback);
	}

	const bool RemoveSpecialActiveCallback(const SpecialInputs key, void (*callback)(void)) {
		return RemoveCallback(special_active_callback_dict, key, callback);
	}

	// --- Mouse --- //

	void AddMouseDownCallback(const MouseInputs input, void (*callback)(void)) {
		AddCallback(mouse_down_callback_dict, input, callback);
	}

	const bool RemoveMouseDownCallback(const MouseInputs input, void(*callback)(void)) {
		return RemoveCallback(mouse_down_callback_dict, input, callback);
	}

	void AddMouseUpCallback(const MouseInputs input, void(*callback)(void)) {
		AddCallback(mouse_up_callback_dict, input, callback);
	}

	const bool RemoveMouseUpCallback(const MouseInputs input, void(*callback)(void)) {
		return RemoveCallback(mouse_up_callback_dict, input, callback);
	}

	void AddMouseMoveCallback(void(*callback)(void)) {
		mouse_move_callbacks.push_back((*(intptr*)(&callback)));
	}

	const bool RemoveMouseMoveCallback(void(*callback)(void)) {
		intptr_vec::iterator it = std::find(mouse_move_callbacks.begin(), mouse_move_callbacks.end(), (*(intptr*)(&callback))); //  (*(intptr*)(&callback))) again, retrieves the pointer to the callback.

		if (it == mouse_move_callbacks.end()) return false;

		mouse_move_callbacks.erase(it);

		return true;
	}

	void AddMouseDragCallback(void(*callback)(void)) {
		mouse_drag_callbacks.push_back((*(intptr*)(&callback)));
	}

	const bool RemoveMouseDragCallback(void(*callback)(void)) {
		intptr_vec::iterator it = std::find(mouse_drag_callbacks.begin(), mouse_drag_callbacks.end(), (*(intptr*)(&callback))); //  (*(intptr*)(&callback))) again, retrieves the pointer to the callback.

		if (it == mouse_drag_callbacks.end()) return false;

		mouse_drag_callbacks.erase(it);

		return true;
	}

	template<size_t bitset_size>
	void RunActiveCallbacks(intptr_vec_uint_umap dictionary, std::bitset<bitset_size> state) {
		for (auto kv : dictionary) {

			if (state[kv.first])
				RunCallbacksInPtrVector(kv.second);
		}
	}

	void RunAllActiveCallbacks() {
		if (has_namespace_been_initialised && enabled)
			RunActiveCallbacks(keyboard_active_callback_dict, inputState.keyboard);
			RunActiveCallbacks(special_active_callback_dict, inputState.special);
			RunActiveCallbacks(mouse_active_callback_dict, inputState.mouse);
	}
}