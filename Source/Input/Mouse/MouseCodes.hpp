#pragma once
#include <GLFW/glfw3.h>

// Mouse codes From glfw3.h
typedef enum class MouseCode : std::uint16_t
{
	Button0 = GLFW_MOUSE_BUTTON_1,
	Button1 = GLFW_MOUSE_BUTTON_2,
	Button2 = GLFW_MOUSE_BUTTON_3,
	Button3 = GLFW_MOUSE_BUTTON_4,
	Button4 = GLFW_MOUSE_BUTTON_5,
	Button5 = GLFW_MOUSE_BUTTON_6,
	Button6 = GLFW_MOUSE_BUTTON_7,
	Button7 = GLFW_MOUSE_BUTTON_8,

	ButtonLast = Button7,
	ButtonLeft = Button0,
	ButtonRight = Button1,
	ButtonMiddle = Button2
} Mouse;

inline std::ostream& operator<<(std::ostream& os, const MouseCode& keyCode)
{
	return os << static_cast<std::uint16_t>(keyCode);
}


#define ENIGMA_MOUSE_BUTTON_0      Mouse::Button0
#define ENIGMA_MOUSE_BUTTON_1      Mouse::Button1
#define ENIGMA_MOUSE_BUTTON_2      Mouse::Button2
#define ENIGMA_MOUSE_BUTTON_3      Mouse::Button3
#define ENIGMA_MOUSE_BUTTON_4      Mouse::Button4
#define ENIGMA_MOUSE_BUTTON_5      Mouse::Button5
#define ENIGMA_MOUSE_BUTTON_6      Mouse::Button6
#define ENIGMA_MOUSE_BUTTON_7      Mouse::Button7
#define ENIGMA_MOUSE_BUTTON_LAST   Mouse::ButtonLast
#define ENIGMA_MOUSE_BUTTON_LEFT   Mouse::ButtonLeft
#define ENIGMA_MOUSE_BUTTON_RIGHT  Mouse::ButtonRight
#define ENIGMA_MOUSE_BUTTON_MIDDLE Mouse::ButtonMiddle
