#ifndef _MOUSE
#define _MOUSE

#include "../utiles/utilidades.h"
#include "screen.h"
#include "../log/log.h"

class EXPORTAR_UTILIDADES Mouse {
	static bool encima;
	static float x;
	static float y;
	
public:
	static bool mouseOver();
	/*
	Return the position of mouse in relation of screen
	*/
	static void getPosition(float& x, float& y);
	void setPosition(float x, float y,unsigned long flags);
	void setOver(bool over);
	//void setButtonDown(float x, float y);
	//void setButtonUp(int button, );

};
#endif // !_MOUSE
