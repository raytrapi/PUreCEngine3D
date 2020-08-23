#include"main.h"
REGISTRAR_MODULO(JHormiguero);

void JHormiguero::update() {
	std::chrono::system_clock::time_point anterior = std::chrono::system_clock::now();
	float radio=2;
	float linea = Screen::getWidth();
	std::vector<Hormiga*>hormigas = hormiguero->cogerHormigas();
	/*for (std::vector<Hormiga*>::iterator it = hormigas.begin(); it != hormigas.end(); it++) { //Para cada hormiga

		Hormiga* hormiga = (*it);
		long posicion = (hormiga->cogerY()*linea + hormiga->cogerX())*4;
		lienzo[posicion++] = 0;
		lienzo[posicion++] = 0;
		lienzo[posicion++] = 0;
		lienzo[posicion++] = 0;
	}*/


	/**/
	//Pintamos el mundo
	unsigned long pos = 0;
	unsigned long pos_i = 0;
	for (long y = 0; y < Screen::getHeight(); y++) {
		for (long x = 0; x < Screen::getWidth(); x++) {
			float c = 0;
			bool conComida = comida[pos_i] > 0;
			float hComida = hormonasComida[pos_i];
			float hHormiga = hormonasHormiga[pos_i];
			for (int k = 0; k < 3; k++) {
				c = entorno[pos + k] * entorno[pos + 3];
				if (conComida) {
					if (k == 1) { //Si es verde
						c = 1;
					} else {
						c = 0;
					}
				}
				
				if (c > 1) {
					c = 1;
				}
				lienzo[pos + k] = c;
			}

			//Controla la hormona de la hormiga
			if (hHormiga > 0) {
				if (hHormiga >= 1) {
					lienzo[pos] = 0.4f;
					lienzo[pos+1] = 0.4f;
					lienzo[pos+2] = 0.4f;
				} else {
					lienzo[pos] = (lienzo[pos]+0.4f*hHormiga)*.5f;
					lienzo[pos + 1] = (lienzo[pos+1] + 0.4f * hHormiga) * .5f;
					lienzo[pos + 2] = (lienzo[pos+2] + 0.4f * hHormiga) * .5f;
				}
				hormonasHormiga[pos_i] -= 0.01;
			}

			pos += 4;
			pos_i += 1;
		}
	}


	for (std::vector<Hormiga*>::iterator it = hormigas.begin(); it != hormigas.end(); it++) {
		Hormiga* hormiga = (*it);
		hormiga->mover(2, 2, Screen::getWidth()-2,Screen::getHeight()-2);
		unsigned long posicionHormona = ((hormiga->cogerY()) * linea + (hormiga->cogerX() ));
		hormonasHormiga[posicionHormona] += 5;
		for (int i = -1; i < 1; i++) {
			for (int j = -1; j < 1; j++) {
				unsigned long posicion = ((hormiga->cogerY()+j) * linea + (hormiga->cogerX()+i)) * 4;
				if (posicion > 0) {
					lienzo[posicion++] = 1;
					lienzo[posicion++] = 1;
					lienzo[posicion++] = 1;
					lienzo[posicion++] = 1;
				}
			}
		}/**/
		
	}/**/
	/*long posicion = 0;
	for (long y = 0; y < Screen::getHeight(); y++) {
		for (long x = 0; x < Screen::getWidth(); x++) {
			lienzo[posicion++] = 1;
			lienzo[posicion++] = 0;
			lienzo[posicion++] = 0;
			lienzo[posicion++] = 1;
		}
	}/**/
	std::chrono::system_clock::time_point actual = std::chrono::system_clock::now();
	double delta = std::chrono::duration_cast<std::chrono::nanoseconds>(actual - anterior).count();
	/*if (tiempoEjecucion > 0) {
		tiempoEjecucion = (tiempoEjecucion + delta) * 0.5;
	}
	else {
		tiempoEjecucion = delta;
	}/**/
	segundos += Time::deltaTime();
	if (segundos >= 1) {
		segundos = 0;
		debug(delta);
	}
	/**/
}

void JHormiguero::start() {
	std::srand(std::time(0));
	xHormiguero = Screen::getWidth() * 0.5;
	yHormiguero = Screen::getHeight() * .5;
	hormiguero = new Hormiguero(xHormiguero, yHormiguero, 10000);
	//Creamos un render de tipo gráfico
	renderable::Img* img = Renderable::createRenderable<renderable::Img>();
	img->setSize(Screen::getWidth(), Screen::getHeight());
	lienzo=img->getData();
	long tamañoLienzo = Screen::getWidth() * Screen::getHeight();
	comida = new int[tamañoLienzo];
	hormonasComida = new float[tamañoLienzo];
	hormonasHormiga = new float[tamañoLienzo];
	entorno = new float[tamañoLienzo*4];
	long pos = 0;
	long pos_i = 0;
	for (long y = 0; y < Screen::getHeight(); y++) {
		for (long x = 0; x < Screen::getWidth(); x++) {
			comida[pos_i] = 0;// (std::rand() % 1001) > 990 ? 1 : 0;
			hormonasComida[pos_i] = 0.f;
			hormonasHormiga[pos_i] = 0.f;
			entorno[pos] = 0;
			entorno[pos + 1] = 0;
			entorno[pos + 2] = 0;
			entorno[pos + 3] = 0;
			pos += 4;
			pos_i++;
		}
	}
	for (float r = 0; r < M_PI * 2; r += 0.01f) {
		long x = xHormiguero + (2 * cos(r));
		long y = yHormiguero + (2 * sin(r));
		long posicion = (y * Screen::getWidth() + x) * 4;
		entorno[posicion] = 0;
		entorno[posicion+1] = 1;
		entorno[posicion+2] = 0;
		entorno[posicion+3] = 1;
	}
}


void JHormiguero::destroy(){
	delete hormiguero;
	delete[] comida;
	delete[]hormonasComida;
	delete[]hormonasHormiga;
	delete[]entorno;
}
