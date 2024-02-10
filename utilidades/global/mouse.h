#ifndef _MOUSE
#define _MOUSE

#include "../utiles/utilidades.h"
#include "screen.h"
//#include "../log/log.h"
#include <tuple>
#include <map>

class EXPORTAR_UTILIDADES Mouse {
	static bool encima;
	static std::map<double, bool> botones;
	static int botonesBit;
protected:
	static double x;
	static double y;
public:
	enum BUTTOMS { LEFT,RIGHT,MIDDLE, FUNC1, FUN2 };
	//static bool mouseOver();
	/*
	Return the position of mouse in relation of screen
	*/
	static std::tuple<double, double> getPosition();
	static void setPosition(double x, double y);
	//void setOver(bool over);
	static void setButtomDown(BUTTOMS buttom, int mod);
	static void setButtomUp(BUTTOMS buttom, int mod);
	static bool isButtomPress(BUTTOMS buttom);
	static int getButtons();
};
#endif // !_MOUSE
