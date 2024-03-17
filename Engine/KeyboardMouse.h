#ifndef KEYBOARDMOUSE_H
#define KEYBOARDMOUSE_H

#include <unordered_map>

class Command;

class KeyboardMouse
{
public:

	KeyboardMouse() = default;
	~KeyboardMouse() = default;

	KeyboardMouse(const KeyboardMouse& other) = delete;
	KeyboardMouse(KeyboardMouse&& other) noexcept = delete;
	KeyboardMouse& operator=(const KeyboardMouse& other) = delete;
	KeyboardMouse& operator=(KeyboardMouse&& other) noexcept = delete;

	void ProcessInput();

private:

	/*Command* move_up;
	Command* move_down;
	Command* move_left;
	Command* move_right;*/

	//std::unordered_map<int, Command*> m_KeyboardMouseCommands;
};

#endif // !KEYBOARDMOUSE_H