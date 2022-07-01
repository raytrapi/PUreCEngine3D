#ifndef _INPUT
#define _INPUT

#include "../utiles/utilidades.h"
//#include "log.h"
//#include ""
#include <string>
#include <map>
#include <vector>
#include <list>
#include <functional>
class Tecla {
	bool pulsada = false;
public:
	bool estaPulsada() { return pulsada; };
	void pulsar() { pulsada = true; };
	void soltar() { pulsada = false; };
};
enum class EXPORTAR_UTILIDADES Key {
	
	NONE,SPACE=32,N0=48,N1,N2,N3,N4,N5,N6,N7,N8,N9,
	A=65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, 
	ARROW_RIGHT=262, ARROW_LEFT, ARROW_DOWN, ARROW_UP,
	F1=290, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
	UP, DOWN, LEFT, RIGHT
	
};

//GLFW_KEY_SPACE	32, GLFW_KEY_APOSTROPHE 39, GLFW_KEY_COMMA 44, GLFW_KEY_MINUS 45, GLFW_KEY_PERIOD 46, GLFW_KEY_SLASH 47,, GLFW_KEY_SEMICOLON 59, GLFW_KEY_EQUAL 61, GLFW_KEY_LEFT_BRACKET 91, GLFW_KEY_BACKSLASH 92, GLFW_KEY_RIGHT_BRACKET 93, GLFW_KEY_GRAVE_ACCENT 96, GLFW_KEY_WORLD_1 161, GLFW_KEY_WORLD_2 162, GLFW_KEY_ESCAPE 256, GLFW_KEY_ENTER 257, GLFW_KEY_TAB 258, GLFW_KEY_BACKSPACE 259, GLFW_KEY_INSERT 260, GLFW_KEY_DELETE 261, GLFW_KEY_RIGHT 262, GLFW_KEY_LEFT 263, GLFW_KEY_DOWN 264, GLFW_KEY_UP 265, GLFW_KEY_PAGE_UP 266, GLFW_KEY_PAGE_DOWN 267, GLFW_KEY_HOME 268, GLFW_KEY_END 269, GLFW_KEY_CAPS_LOCK 280, GLFW_KEY_SCROLL_LOCK 281, GLFW_KEY_NUM_LOCK 282, GLFW_KEY_PRINT_SCREEN 283, GLFW_KEY_PAUSE 284, GLFW_KEY_KP_0 320, GLFW_KEY_KP_1 321, GLFW_KEY_KP_2 322, GLFW_KEY_KP_3 323, GLFW_KEY_KP_4 324, GLFW_KEY_KP_5 325, GLFW_KEY_KP_6 326, GLFW_KEY_KP_7 327, GLFW_KEY_KP_8 328, GLFW_KEY_KP_9 329, GLFW_KEY_KP_DECIMAL 330, GLFW_KEY_KP_DIVIDE 331, GLFW_KEY_KP_MULTIPLY 332, GLFW_KEY_KP_SUBTRACT 333, GLFW_KEY_KP_ADD 334, GLFW_KEY_KP_ENTER 335, GLFW_KEY_KP_EQUAL 336, GLFW_KEY_LEFT_SHIFT 340, GLFW_KEY_LEFT_CONTROL 341, GLFW_KEY_LEFT_ALT 342, GLFW_KEY_LEFT_SUPER 343, GLFW_KEY_RIGHT_SHIFT 344, GLFW_KEY_RIGHT_CONTROL 345, GLFW_KEY_RIGHT_ALT 346, GLFW_KEY_RIGHT_SUPER 347, GLFW_KEY_MENU 348
class EXPORTAR_UTILIDADES Input {
	static std::map <Key, Tecla> teclas;
	//static std::vector<void (*)(Key)> eventosKeyPress; //Guardamos los eventos de pulsación de tecla
	static Key traducirTecla(unsigned int key);
	static std::map<Key, std::vector<Key>>mapeadas;
	static std::map<Key,Tecla*> presionadas;
	std::vector<std::tuple<Key, std::function<void(Key)>, bool>> controlTeclasPulsadas;
	//static Input* instancia;
	
public:
	/*Input() {
		if (instancia == NULL) {
			instancia = this;
		}
	}
	
	Input* getInstance() {
		if (instancia == NULL) {
			instancia = new Input();
		}
		return instancia;
	}
	void setInstance(Input* i) { instancia = i; };/**/
	bool isKeyDown(Key key);
	bool isKeyUp(Key key);
	bool isKeyPress(Key key);
	void onKeyPress(Key key, std::function<void(Key)>);
	static void setKeyDown(unsigned int key, long extra);
	static void setKeyUp(unsigned int key, long extra);
	void resetKeyPress();
	void checkKeysPress();
	void resetAllKeysPress() { 
		controlTeclasPulsadas.clear(); 
	}
	//static void onPress(void (*f)(Key));
};
/*Input* Input::instancia;
std::vector<std::tuple<Key, std::function<void(Key)>, bool>> Input::controlTeclasPulsadas;*/
#endif // !_INPUT
