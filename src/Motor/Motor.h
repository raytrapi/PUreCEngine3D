#ifndef _MOTORGRAFICO
#define _MOTORGRAFICO

class MotorGrafico{
	public:
		virtual void renderizar()=0;
		virtual void inicializar(HWND, double, double) = 0;

};

#endif // 