#include"main.h"
REGISTRAR_MODULO(Hormiguero);

void Hormiguero::update() {
	for (int y = 0; y < Screen::getHeight(); y++) {
		for (int x = 0; x < Screen::getWidth(); x++) {
			renderable::Pixel* p = lienzo->getPixel(x, y);
			if (subiendo){
				if (p->R() < 1) {
					p->setColor(p->R() + (0.01*Time::deltaTime()), p->G(), p->B(), p->A());
				}else {
					subiendo = false;
				}
			}else {
				if (p->R() < 0) {
					p->setColor(p->R() - (0.01*Time::deltaTime()), p->G(), p->B(), p->A());
				}
				else {
					subiendo = true;
				}
			}
			lienzo->setPixel(x,y,p);
		}
	}
	/**/
}

void Hormiguero::start() {
	debug("Iniciamos");
	//Creamos un render de tipo gráfico
	lienzo=Renderable::createRenderable<renderable::Img>();
}
