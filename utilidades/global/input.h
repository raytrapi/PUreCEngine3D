#ifndef _INPUT
#define _INPUT

#include "../utiles/utilidades.h"
#include <map>
#include <vector>
#include <list>
class Tecla {
	bool pulsada = false;
public:
	bool estaPulsada() { return pulsada; };
	void pulsar() { pulsada = true; };
	void soltar() { pulsada = false; };
};
enum class EXPORTAR_UTILIDADES Key {
	NONE,A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, 
	UP, DONW, LEFT, RIGHT,
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
};
class EXPORTAR_UTILIDADES Input {
	static std::map <Key, Tecla> teclas;
	//static std::vector<void (*)(Key)> eventosKeyPress; //Guardamos los eventos de pulsación de tecla
	Key traducirTecla(unsigned int key);
	static std::map<Key,Tecla*> presionadas;
public:
	static bool isKeyDown(Key key);
	static bool isKeyUp(Key key);
	static bool isKeyPress(Key key);
	void setKeyDown(unsigned int key, long extra);
	void setKeyUp(unsigned int key, long extra);
	void resetKeyPress();
	//static void onPress(void (*f)(Key));
};
#endif // !_INPUT
