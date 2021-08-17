#pragma once
#include <GLFW/glfw3.h>

//Keycodes From glfw3.h
typedef enum class KeyCode : std::uint16_t
{
	Space = GLFW_KEY_SPACE,
	Apostrophe = GLFW_KEY_APOSTROPHE, /* ' */
	Comma = GLFW_KEY_COMMA, /* , */
	Minus = GLFW_KEY_MINUS, /* - */
	Period = GLFW_KEY_PERIOD, /* . */
	Slash = GLFW_KEY_SLASH, /* / */
	
	D0 = GLFW_KEY_0, /* 0 */
	D1 = GLFW_KEY_1, /* 1 */
	D2 = GLFW_KEY_2, /* 2 */
	D3 = GLFW_KEY_3, /* 3 */
	D4 = GLFW_KEY_4, /* 4 */
	D5 = GLFW_KEY_5, /* 5 */
	D6 = GLFW_KEY_6, /* 6 */
	D7 = GLFW_KEY_7, /* 7 */
	D8 = GLFW_KEY_8, /* 8 */
	D9 = GLFW_KEY_9, /* 9 */

	Semicolon = GLFW_KEY_SEMICOLON, /* ; */
	Equal = GLFW_KEY_EQUAL, /* = */

	A = GLFW_KEY_A,
	B = GLFW_KEY_B,
	C = GLFW_KEY_C,
	D = GLFW_KEY_D,
	E = GLFW_KEY_E,
	F = GLFW_KEY_F,
	G = GLFW_KEY_G,
	H = GLFW_KEY_H,
	I = GLFW_KEY_I,
	J = GLFW_KEY_J,
	K = GLFW_KEY_K,
	L = GLFW_KEY_L,
	M = GLFW_KEY_M,
	N = GLFW_KEY_N,
	O = GLFW_KEY_O,
	P = GLFW_KEY_P,
	Q = GLFW_KEY_Q,
	R = GLFW_KEY_R,
	S = GLFW_KEY_S,
	T = GLFW_KEY_T,
	U = GLFW_KEY_U,
	V = GLFW_KEY_V,
	W = GLFW_KEY_W,
	X = GLFW_KEY_X,
	Y = GLFW_KEY_Y,
	Z = GLFW_KEY_Z,

	LeftBracket = GLFW_KEY_LEFT_BRACKET,  /* [ */
	Backslash = GLFW_KEY_BACKSLASH,  /* \ */
	RightBracket = GLFW_KEY_RIGHT_BRACKET,  /* ] */
	GraveAccent = GLFW_KEY_GRAVE_ACCENT,  /* ` */

	World1 = GLFW_KEY_WORLD_1, /* non-US #1 */
	World2 = GLFW_KEY_WORLD_2, /* non-US #2 */

	/* Function keys */
	Escape = GLFW_KEY_ESCAPE,
	Enter = GLFW_KEY_ENTER,	// OR RETURN
	Tab = GLFW_KEY_TAB,
	Backspace = GLFW_KEY_BACKSPACE,
	Insert = GLFW_KEY_INSERT,
	Delete = GLFW_KEY_DELETE,
	Right = GLFW_KEY_RIGHT,
	Left = GLFW_KEY_LEFT,
	Down = GLFW_KEY_DOWN,
	Up = GLFW_KEY_UP,
	PageUp = GLFW_KEY_PAGE_UP,
	PageDown = GLFW_KEY_PAGE_DOWN,
	Home = GLFW_KEY_HOME,
	End = GLFW_KEY_END,
	CapsLock = GLFW_KEY_CAPS_LOCK,
	ScrollLock = GLFW_KEY_SCROLL_LOCK,
	NumLock = GLFW_KEY_NUM_LOCK,
	PrintScreen = GLFW_KEY_PRINT_SCREEN,
	Pause = GLFW_KEY_PAUSE,
	F1 =  GLFW_KEY_F1,
	F2 =  GLFW_KEY_F2,
	F3 =  GLFW_KEY_F3,
	F4 =  GLFW_KEY_F4,
	F5 =  GLFW_KEY_F5,
	F6 =  GLFW_KEY_F6,
	F7 =  GLFW_KEY_F7,
	F8 =  GLFW_KEY_F8,
	F9 =  GLFW_KEY_F9,
	F10 =  GLFW_KEY_F10,
	F11 =  GLFW_KEY_F11,
	F12 =  GLFW_KEY_F12,
	F13 =  GLFW_KEY_F13,
	F14 =  GLFW_KEY_F14,
	F15 =  GLFW_KEY_F15,
	F16 =  GLFW_KEY_F16,
	F17 =  GLFW_KEY_F17,
	F18 =  GLFW_KEY_F18,
	F19 =  GLFW_KEY_F19,
	F20 =  GLFW_KEY_F20,
	F21 =  GLFW_KEY_F21,
	F22 =  GLFW_KEY_F22,
	F23 =  GLFW_KEY_F23,
	F24 =  GLFW_KEY_F24,
	F25 =  GLFW_KEY_F25,

	/* Keypad */
	KP0 =  GLFW_KEY_KP_0,
	KP1 =  GLFW_KEY_KP_1,
	KP2 =  GLFW_KEY_KP_2,
	KP3 =  GLFW_KEY_KP_3,
	KP4 =  GLFW_KEY_KP_4,
	KP5 =  GLFW_KEY_KP_5,
	KP6 =  GLFW_KEY_KP_6,
	KP7 =  GLFW_KEY_KP_7,
	KP8 =  GLFW_KEY_KP_8,
	KP9 =  GLFW_KEY_KP_9,
	KPDecimal = GLFW_KEY_KP_DECIMAL,
	KPDivide = GLFW_KEY_KP_DIVIDE,
	KPMultiply = GLFW_KEY_KP_MULTIPLY,
	KPSubtract = GLFW_KEY_KP_SUBTRACT,
	KPAdd = GLFW_KEY_KP_ADD,
	KPEnter = GLFW_KEY_KP_ENTER,
	KPEqual = GLFW_KEY_KP_EQUAL,

	LeftShift = GLFW_KEY_LEFT_SHIFT,
	LeftControl = GLFW_KEY_LEFT_CONTROL,
	LeftAlt = GLFW_KEY_LEFT_ALT,
	LeftSuper = GLFW_KEY_LEFT_SUPER,
	RightShift = GLFW_KEY_RIGHT_SHIFT,
	RightControl = GLFW_KEY_RIGHT_CONTROL,
	RightAlt = GLFW_KEY_RIGHT_ALT,
	RightSuper = GLFW_KEY_RIGHT_SUPER,
	Menu = GLFW_KEY_MENU
} Key;


inline std::ostream& operator<<(std::ostream& os, const KeyCode& keyCode)
{
	return os << static_cast<std::uint16_t>(keyCode);
}


#define ENIGMA_KEY_SPACE           Key::Space
#define ENIGMA_KEY_APOSTROPHE      Key::Apostrophe    /* ' */
#define ENIGMA_KEY_COMMA           Key::Comma         /* , */
#define ENIGMA_KEY_MINUS           Key::Minus         /* - */
#define ENIGMA_KEY_PERIOD          Key::Period        /* . */
#define ENIGMA_KEY_SLASH           Key::Slash         /* / */
#define ENIGMA_KEY_0               Key::D0
#define ENIGMA_KEY_1               Key::D1
#define ENIGMA_KEY_2               Key::D2
#define ENIGMA_KEY_3               Key::D3
#define ENIGMA_KEY_4               Key::D4
#define ENIGMA_KEY_5               Key::D5
#define ENIGMA_KEY_6               Key::D6
#define ENIGMA_KEY_7               Key::D7
#define ENIGMA_KEY_8               Key::D8
#define ENIGMA_KEY_9               Key::D9
#define ENIGMA_KEY_SEMICOLON       Key::Semicolon     /* ; */
#define ENIGMA_KEY_EQUAL           Key::Equal         /* = */
#define ENIGMA_KEY_A               Key::A
#define ENIGMA_KEY_B               Key::B
#define ENIGMA_KEY_C               Key::C
#define ENIGMA_KEY_D               Key::D
#define ENIGMA_KEY_E               Key::E
#define ENIGMA_KEY_F               Key::F
#define ENIGMA_KEY_G               Key::G
#define ENIGMA_KEY_H               Key::H
#define ENIGMA_KEY_I               Key::I
#define ENIGMA_KEY_J               Key::J
#define ENIGMA_KEY_K               Key::K
#define ENIGMA_KEY_L               Key::L
#define ENIGMA_KEY_M               Key::M
#define ENIGMA_KEY_N               Key::N
#define ENIGMA_KEY_O               Key::O
#define ENIGMA_KEY_P               Key::P
#define ENIGMA_KEY_Q               Key::Q
#define ENIGMA_KEY_R               Key::R
#define ENIGMA_KEY_S               Key::S
#define ENIGMA_KEY_T               Key::T
#define ENIGMA_KEY_U               Key::U
#define ENIGMA_KEY_V               Key::V
#define ENIGMA_KEY_W               Key::W
#define ENIGMA_KEY_X               Key::X
#define ENIGMA_KEY_Y               Key::Y
#define ENIGMA_KEY_Z               Key::Z
#define ENIGMA_KEY_LEFT_BRACKET    Key::LeftBracket   /* [ */
#define ENIGMA_KEY_BACKSLASH       Key::Backslash     /* \ */
#define ENIGMA_KEY_RIGHT_BRACKET   Key::RightBracket  /* ] */
#define ENIGMA_KEY_GRAVE_ACCENT    Key::GraveAccent   /* ` */
#define ENIGMA_KEY_WORLD_1         Key::World1        /* non-US #1 */
#define ENIGMA_KEY_WORLD_2         Key::World2        /* non-US #2 */

/* Function keys */
#define ENIGMA_KEY_ESCAPE          Key::Escape
#define ENIGMA_KEY_ENTER           Key::Enter
#define ENIGMA_KEY_TAB             Key::Tab
#define ENIGMA_KEY_BACKSPACE       Key::Backspace
#define ENIGMA_KEY_INSERT          Key::Insert
#define ENIGMA_KEY_DELETE          Key::Delete
#define ENIGMA_KEY_RIGHT           Key::Right
#define ENIGMA_KEY_LEFT            Key::Left
#define ENIGMA_KEY_DOWN            Key::Down
#define ENIGMA_KEY_UP              Key::Up
#define ENIGMA_KEY_PAGE_UP         Key::PageUp
#define ENIGMA_KEY_PAGE_DOWN       Key::PageDown
#define ENIGMA_KEY_HOME            Key::Home
#define ENIGMA_KEY_END             Key::End
#define ENIGMA_KEY_CAPS_LOCK       Key::CapsLock
#define ENIGMA_KEY_SCROLL_LOCK     Key::ScrollLock
#define ENIGMA_KEY_NUM_LOCK        Key::NumLock
#define ENIGMA_KEY_PRINT_SCREEN    Key::PrintScreen
#define ENIGMA_KEY_PAUSE           Key::Pause
#define ENIGMA_KEY_F1              Key::F1
#define ENIGMA_KEY_F2              Key::F2
#define ENIGMA_KEY_F3              Key::F3
#define ENIGMA_KEY_F4              Key::F4
#define ENIGMA_KEY_F5              Key::F5
#define ENIGMA_KEY_F6              Key::F6
#define ENIGMA_KEY_F7              Key::F7
#define ENIGMA_KEY_F8              Key::F8
#define ENIGMA_KEY_F9              Key::F9
#define ENIGMA_KEY_F10             Key::F10
#define ENIGMA_KEY_F11             Key::F11
#define ENIGMA_KEY_F12             Key::F12
#define ENIGMA_KEY_F13             Key::F13
#define ENIGMA_KEY_F14             Key::F14
#define ENIGMA_KEY_F15             Key::F15
#define ENIGMA_KEY_F16             Key::F16
#define ENIGMA_KEY_F17             Key::F17
#define ENIGMA_KEY_F18             Key::F18
#define ENIGMA_KEY_F19             Key::F19
#define ENIGMA_KEY_F20             Key::F20
#define ENIGMA_KEY_F21             Key::F21
#define ENIGMA_KEY_F22             Key::F22
#define ENIGMA_KEY_F23             Key::F23
#define ENIGMA_KEY_F24             Key::F24
#define ENIGMA_KEY_F25             Key::F25

/* Keypad */
#define ENIGMA_KEY_KP_0            Key::KP0
#define ENIGMA_KEY_KP_1            Key::KP1
#define ENIGMA_KEY_KP_2            Key::KP2
#define ENIGMA_KEY_KP_3            Key::KP3
#define ENIGMA_KEY_KP_4            Key::KP4
#define ENIGMA_KEY_KP_5            Key::KP5
#define ENIGMA_KEY_KP_6            Key::KP6
#define ENIGMA_KEY_KP_7            Key::KP7
#define ENIGMA_KEY_KP_8            Key::KP8
#define ENIGMA_KEY_KP_9            Key::KP9
#define ENIGMA_KEY_KP_DECIMAL      Key::KPDecimal
#define ENIGMA_KEY_KP_DIVIDE       Key::KPDivide
#define ENIGMA_KEY_KP_MULTIPLY     Key::KPMultiply
#define ENIGMA_KEY_KP_SUBTRACT     Key::KPSubtract
#define ENIGMA_KEY_KP_ADD          Key::KPAdd
#define ENIGMA_KEY_KP_ENTER        Key::KPEnter
#define ENIGMA_KEY_KP_EQUAL        Key::KPEqual

#define ENIGMA_KEY_LEFT_SHIFT      Key::LeftShift
#define ENIGMA_KEY_LEFT_CONTROL    Key::LeftControl
#define ENIGMA_KEY_LEFT_ALT        Key::LeftAlt
#define ENIGMA_KEY_LEFT_SUPER      Key::LeftSuper
#define ENIGMA_KEY_RIGHT_SHIFT     Key::RightShift
#define ENIGMA_KEY_RIGHT_CONTROL   Key::RightControl
#define ENIGMA_KEY_RIGHT_ALT       Key::RightAlt
#define ENIGMA_KEY_RIGHT_SUPER     Key::RightSuper
#define ENIGMA_KEY_MENU            Key::Menu