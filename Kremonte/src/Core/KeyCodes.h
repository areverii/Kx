#pragma once

namespace Kremonte {

	typedef enum class KeyCode : uint16_t {

		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define KR_KEY_SPACE           ::Kremonte::Key::Space
#define KR_KEY_APOSTROPHE      ::Kremonte::Key::Apostrophe    /* ' */
#define KR_KEY_COMMA           ::Kremonte::Key::Comma         /* , */
#define KR_KEY_MINUS           ::Kremonte::Key::Minus         /* - */
#define KR_KEY_PERIOD          ::Kremonte::Key::Period        /* . */
#define KR_KEY_SLASH           ::Kremonte::Key::Slash         /* / */
#define KR_KEY_0               ::Kremonte::Key::D0
#define KR_KEY_1               ::Kremonte::Key::D1
#define KR_KEY_2               ::Kremonte::Key::D2
#define KR_KEY_3               ::Kremonte::Key::D3
#define KR_KEY_4               ::Kremonte::Key::D4
#define KR_KEY_5               ::Kremonte::Key::D5
#define KR_KEY_6               ::Kremonte::Key::D6
#define KR_KEY_7               ::Kremonte::Key::D7
#define KR_KEY_8               ::Kremonte::Key::D8
#define KR_KEY_9               ::Kremonte::Key::D9
#define KR_KEY_SEMICOLON       ::Kremonte::Key::Semicolon     /* ; */
#define KR_KEY_EQUAL           ::Kremonte::Key::Equal         /* = */
#define KR_KEY_A               ::Kremonte::Key::A
#define KR_KEY_B               ::Kremonte::Key::B
#define KR_KEY_C               ::Kremonte::Key::C
#define KR_KEY_D               ::Kremonte::Key::D
#define KR_KEY_E               ::Kremonte::Key::E
#define KR_KEY_F               ::Kremonte::Key::F
#define KR_KEY_G               ::Kremonte::Key::G
#define KR_KEY_H               ::Kremonte::Key::H
#define KR_KEY_I               ::Kremonte::Key::I
#define KR_KEY_J               ::Kremonte::Key::J
#define KR_KEY_K               ::Kremonte::Key::K
#define KR_KEY_L               ::Kremonte::Key::L
#define KR_KEY_M               ::Kremonte::Key::M
#define KR_KEY_N               ::Kremonte::Key::N
#define KR_KEY_O               ::Kremonte::Key::O
#define KR_KEY_P               ::Kremonte::Key::P
#define KR_KEY_Q               ::Kremonte::Key::Q
#define KR_KEY_R               ::Kremonte::Key::R
#define KR_KEY_S               ::Kremonte::Key::S
#define KR_KEY_T               ::Kremonte::Key::T
#define KR_KEY_U               ::Kremonte::Key::U
#define KR_KEY_V               ::Kremonte::Key::V
#define KR_KEY_W               ::Kremonte::Key::W
#define KR_KEY_X               ::Kremonte::Key::X
#define KR_KEY_Y               ::Kremonte::Key::Y
#define KR_KEY_Z               ::Kremonte::Key::Z
#define KR_KEY_LEFT_BRACKET    ::Kremonte::Key::LeftBracket   /* [ */
#define KR_KEY_BACKSLASH       ::Kremonte::Key::Backslash     /* \ */
#define KR_KEY_RIGHT_BRACKET   ::Kremonte::Key::RightBracket  /* ] */
#define KR_KEY_GRAVE_ACCENT    ::Kremonte::Key::GraveAccent   /* ` */
#define KR_KEY_WORLD_1         ::Kremonte::Key::World1        /* non-US #1 */
#define KR_KEY_WORLD_2         ::Kremonte::Key::World2        /* non-US #2 */

/* Function keys */
#define KR_KEY_ESCAPE          ::Kremonte::Key::Escape
#define KR_KEY_ENTER           ::Kremonte::Key::Enter
#define KR_KEY_TAB             ::Kremonte::Key::Tab
#define KR_KEY_BACKSPACE       ::Kremonte::Key::Backspace
#define KR_KEY_INSERT          ::Kremonte::Key::Insert
#define KR_KEY_DELETE          ::Kremonte::Key::Delete
#define KR_KEY_RIGHT           ::Kremonte::Key::Right
#define KR_KEY_LEFT            ::Kremonte::Key::Left
#define KR_KEY_DOWN            ::Kremonte::Key::Down
#define KR_KEY_UP              ::Kremonte::Key::Up
#define KR_KEY_PAGE_UP         ::Kremonte::Key::PageUp
#define KR_KEY_PAGE_DOWN       ::Kremonte::Key::PageDown
#define KR_KEY_HOME            ::Kremonte::Key::Home
#define KR_KEY_END             ::Kremonte::Key::End
#define KR_KEY_CAPS_LOCK       ::Kremonte::Key::CapsLock
#define KR_KEY_SCROLL_LOCK     ::Kremonte::Key::ScrollLock
#define KR_KEY_NUM_LOCK        ::Kremonte::Key::NumLock
#define KR_KEY_PRINT_SCREEN    ::Kremonte::Key::PrintScreen
#define KR_KEY_PAUSE           ::Kremonte::Key::Pause
#define KR_KEY_F1              ::Kremonte::Key::F1
#define KR_KEY_F2              ::Kremonte::Key::F2
#define KR_KEY_F3              ::Kremonte::Key::F3
#define KR_KEY_F4              ::Kremonte::Key::F4
#define KR_KEY_F5              ::Kremonte::Key::F5
#define KR_KEY_F6              ::Kremonte::Key::F6
#define KR_KEY_F7              ::Kremonte::Key::F7
#define KR_KEY_F8              ::Kremonte::Key::F8
#define KR_KEY_F9              ::Kremonte::Key::F9
#define KR_KEY_F10             ::Kremonte::Key::F10
#define KR_KEY_F11             ::Kremonte::Key::F11
#define KR_KEY_F12             ::Kremonte::Key::F12
#define KR_KEY_F13             ::Kremonte::Key::F13
#define KR_KEY_F14             ::Kremonte::Key::F14
#define KR_KEY_F15             ::Kremonte::Key::F15
#define KR_KEY_F16             ::Kremonte::Key::F16
#define KR_KEY_F17             ::Kremonte::Key::F17
#define KR_KEY_F18             ::Kremonte::Key::F18
#define KR_KEY_F19             ::Kremonte::Key::F19
#define KR_KEY_F20             ::Kremonte::Key::F20
#define KR_KEY_F21             ::Kremonte::Key::F21
#define KR_KEY_F22             ::Kremonte::Key::F22
#define KR_KEY_F23             ::Kremonte::Key::F23
#define KR_KEY_F24             ::Kremonte::Key::F24
#define KR_KEY_F25             ::Kremonte::Key::F25

/* Keypad */
#define KR_KEY_KP_0            ::Kremonte::Key::KP0
#define KR_KEY_KP_1            ::Kremonte::Key::KP1
#define KR_KEY_KP_2            ::Kremonte::Key::KP2
#define KR_KEY_KP_3            ::Kremonte::Key::KP3
#define KR_KEY_KP_4            ::Kremonte::Key::KP4
#define KR_KEY_KP_5            ::Kremonte::Key::KP5
#define KR_KEY_KP_6            ::Kremonte::Key::KP6
#define KR_KEY_KP_7            ::Kremonte::Key::KP7
#define KR_KEY_KP_8            ::Kremonte::Key::KP8
#define KR_KEY_KP_9            ::Kremonte::Key::KP9
#define KR_KEY_KP_DECIMAL      ::Kremonte::Key::KPDecimal
#define KR_KEY_KP_DIVIDE       ::Kremonte::Key::KPDivide
#define KR_KEY_KP_MULTIPLY     ::Kremonte::Key::KPMultiply
#define KR_KEY_KP_SUBTRACT     ::Kremonte::Key::KPSubtract
#define KR_KEY_KP_ADD          ::Kremonte::Key::KPAdd
#define KR_KEY_KP_ENTER        ::Kremonte::Key::KPEnter
#define KR_KEY_KP_EQUAL        ::Kremonte::Key::KPEqual

#define KR_KEY_LEFT_SHIFT      ::Kremonte::Key::LeftShift
#define KR_KEY_LEFT_CONTROL    ::Kremonte::Key::LeftControl
#define KR_KEY_LEFT_ALT        ::Kremonte::Key::LeftAlt
#define KR_KEY_LEFT_SUPER      ::Kremonte::Key::LeftSuper
#define KR_KEY_RIGHT_SHIFT     ::Kremonte::Key::RightShift
#define KR_KEY_RIGHT_CONTROL   ::Kremonte::Key::RightControl
#define KR_KEY_RIGHT_ALT       ::Kremonte::Key::RightAlt
#define KR_KEY_RIGHT_SUPER     ::Kremonte::Key::RightSuper
#define KR_KEY_MENU            ::Kremonte::Key::Menu