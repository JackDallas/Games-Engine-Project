#pragma once
/**
	enum representing the Input Type on the Keyboard
*/
enum Key_InputType {
	KEY_DOWN,
};
/**
	enum representing the Input Type on the Mouse
*/
enum Mouse_InputType {
	MOUSE_MOVEMENT,
	MOUSE_DOWN,
	MOUSE_UP
};
/**
	enum representing the Key being pressed on the keyboard
*/
enum Key_InputKey {
	A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	LEFT = 100, UP, RIGHT, DOWN
};
/**
	enum representing the key being presses on the Mouse
*/
enum Mouse_InputKey {
	MOUSE_LEFT = 0, MOUSE_MIDDLE, MOUSE_RIGHT
};
/**
	struct containting the x and y position of the mouse in pixels
*/
struct Mouse_Position {
	float x;
	float y;
};
/**
	struct containing the info passed to the onKeyEvent()
	@see onKeyEvent()
*/
struct Key_Input {
	Key_InputType type;
	Key_InputKey key;
};
/**
	struct containing the info passed to the onMouseEvent()
	@see onMouseEvent()
*/
struct Mouse_Input {
	Mouse_InputType type;
	Mouse_InputKey key;
	Mouse_Position mousePosition;
};