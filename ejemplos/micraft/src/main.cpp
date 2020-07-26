#include"main.h"
REGISTRAR_MODULO(Minecraft);

void Minecraft::generarTerreno() {
	//Generamos solo 1
	

	//Generamos el mapa
	//Borrar todos los tile
	for (auto it = terrenos.begin(); it != terrenos.end(); it++) {
		delete (*it);
	}
	terrenos.clear();
	//Creamos mapa
	terrenos.push_back(new Terreno(longitudTile));

	terrenos[0]->generar();
	pintarTerreno();
	
}
Terreno * Minecraft::generarTerreno(renderable::Img* renderableTail, Terreno * tierra, Direccion origen) {
	Terreno* t;
	switch (origen) {
	case Direccion::ESTE:
		t = tierra->coger(Direccion::OESTE);
		if (t == 0) {
			t = new Terreno(longitudTile);
		}
		break;
	case Direccion::NORTE:
		t = tierra->coger(Direccion::NORTE);
		if (t == 0) {
			t = new Terreno(longitudTile);
		}
		break;
	case Direccion::OESTE:
		t = tierra->coger(Direccion::ESTE);
		if (t == 0) {
			t = new Terreno(longitudTile);
		}
		
		break;
	case Direccion::SUR:
		t = tierra->coger(Direccion::NORTE);
		if (t == 0) {
			t = new Terreno(longitudTile);
		}
		break;
	
	}
	t->informar(tierra, origen);
	Tipo** porcion = t->generar();
	pintarTerreno();
	return t;
}

void Minecraft::pintarTerreno() {
	Tipo** porcion = terrenos[0]->cogerPorcion();
	/*float* imagenMapa = mapa->getData();
	int anchoVisualTile = mapa->getWidth();
	long pos = 0;
	for (int y1 = 0; y1 < mapa->getHeight(); y1++) {
		for (int x1 = 0; x1 < mapa->getWidth(); x1++) {
			if (x1 < (mapa->getWidth() * 0.5f)) {
				imagenMapa[pos++] = 1;
				imagenMapa[pos++] = 0;
				imagenMapa[pos++] = 0;
				imagenMapa[pos++] = 1;
			} else {
				imagenMapa[pos++] = 1;
				imagenMapa[pos++] = 1;
				imagenMapa[pos++] = 1;
				imagenMapa[pos++] = 1;
			}
		}
	}
	for (int x = 0; x < longitudTile; x++) {
		for (int y = 0; y < longitudTile; y++) {
			for (int y1 = 0; y1 < tamañoVisualPixelTile; y1++) {
				for (int x1 = 0; x1 < tamañoVisualPixelTile; x1++) {
					long posMapa = (((y * tamañoVisualPixelTile) + y1) * anchoVisualTile + ((x * tamañoVisualPixelTile) + x1)) * 4;
					float r = 0;
					float g = 0;
					float b = 0;
					float a = 1;
					switch (porcion[x][y]) {
					case Tipo::TIERRA_SECA:
						r = 0.62f;
						g = 0.33f;
						b = 0.01f;
						break;
					case Tipo::TIERRA_VERDE:
						r = 0.39f;
						g = 0.82f;
						b = 0;
						break;
					case Tipo::PIEDRA:
						r = 0.8f;
						g = 0.8f;
						b = 0.8;
						break;
					case Tipo::AGUA:
						r = 0;
						g = 0;
						b = 1;
						break;

					}
					imagenMapa[posMapa] = r;
					imagenMapa[posMapa + 1] = g;
					imagenMapa[posMapa + 2] = b;
					imagenMapa[posMapa + 3] = a;
				}
			}

		}
	}/**/
}

/*void Minecraft::pressKey(Key k) {
	if (k == Key::M) {
		generarTerreno(mapa);
	}
}*/

Minecraft::Minecraft() {
	setScreenSize(1000, 1000);
}

void Minecraft::update() {
	std::chrono::system_clock::time_point anterior = std::chrono::system_clock::now();

	/*cubo->pX += (10 * Time::deltaTime());
	//cubo->pY += (1 * Time::deltaTime());
	//cubo->pZ += (1 * Time::deltaTime());

	/*cubo->rX += (20 * Time::deltaTime());
	cubo->rY += (35 * Time::deltaTime());
	cubo->rZ += (40 * Time::deltaTime());/**/

	if (Input::isKeyPress(Key::M)) {
		generarTerreno();
	}



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
		//debug(delta);
	}
	/**/
}

void Minecraft::start() {
	/*mapa = Renderable::createRenderable<renderable::Img>();
	radio = 1;
	float lX = longitudTile * tamañoVisualPixelTile;
	float lY = longitudTile * tamañoVisualPixelTile;
	lX += (lX * radio * 2);
	lY += (lY * radio * 2);
	mapa->setSize(lX, lY);
	mapa->setPosition((float)Screen::getWidth() * 0.5 - ((float)lX * 0.5f), (float)Screen::getHeight() * 0.5 - ((float)lY * 0.5f), 0);

	generarTerreno();/**/
	/*//Busco el bloque más a la derecha;
	Terreno* anterior = &terreno;
	while (anterior->coger(Direccion::ESTE) != 0) {
		anterior = anterior->coger(Direccion::ESTE);
	}
	float x = (float)Screen::getWidth() * 0.5 - ((float)lX * 0.5f);
	float y = (float)Screen::getHeight() * 0.5 - ((float)lY * 0.5f);
	float z = 0;
	Direccion direccion = Direccion::NORTE;
	Direccion direccionAnterior= Direccion::OESTE;
	x += lX;
	int numeroBloques = radio * 8;
	Terreno* t;
	for (int i = 0; i < numeroBloques; i++) {
		im = Renderable::createRenderable<renderable::Img>();
		im->setSize(lX, lY);
		mapas.push_back(im);
		t=generarTerreno(im, anterior, direccionAnterior);

		direccionAnterior = direccion;
		im->setPosition(x, y, z);
		//while (anterior->coger(direccion) == 0) {
			switch (direccion) {
			case Direccion::ESTE:
				direccionAnterior = Direccion::OESTE;
				if (t->coger(Direccion::NORTE) == 0) {
					//Giramos a la izquierda
					direccion = Direccion::NORTE;
					y -= lY;
				} else {
					x -= lX;
				}
				break;
			case Direccion::NORTE:
				direccionAnterior = Direccion::SUR;
				if (t->coger(Direccion::OESTE) == 0) {
					//Giramos a la izquierda
					direccion = Direccion::OESTE;
					x -= lX;
				} else {
					y -= lY;
				}
				break;
			case Direccion::OESTE:
				direccionAnterior = Direccion::ESTE;
				if (t->coger(Direccion::SUR) == 0) {
					//Giramos a la izquierda
					direccion = Direccion::SUR;
					y += lY;
				} else {
					x -= lX;
				}
				break;
			case Direccion::SUR:
				direccionAnterior = Direccion::NORTE;
				if (t->coger(Direccion::ESTE) == 0) {
					//Giramos a la izquierda
					direccion = Direccion::ESTE;
					x += lX;
				} else {
					y -= lY;
				}
				break;
			}
			anterior = t;


		//}
	}/**/
	//Minecraft* yo = this;
	//Input::onPress(pressKey);
	mapa = Entity::create<Entity::TYPE::EMPTY>();
	renderable::Img* imagenMapa= mapa->addComponent<renderable::Img>();


	imagenMapa->getId();
	//mapa->loadShader("shaders/vertex_basic.glsl", renderable::Shader::TYPE::VERTEX);
	//mapa->loadShader("shaders/fragment_solid_color.glsl", renderable::Shader::TYPE::FRAGMENT);
	//mapa->compileShader();/**/
	/*unsigned int vs = Graphic->loadShader("shaders/vertex_basic.glsl", renderable::Shader::TYPE::VERTEX,mapa);
	unsigned int fs = Graphic->loadShader("shaders/fragment_solid_color.glsl", renderable::Shader::TYPE::FRAGMENT, mapa);
	Graphic->compileShader(mapa);/**/

	imagenMapa->setPosition(-100,100, -1000);
	imagenMapa->setRotation(-180, 0, 90);
	float* datos = imagenMapa->setSize(Screen::getWidth(),Screen::getHeight());
	long pos = 0;
	for (long y = 0; y < imagenMapa->getHeight(); y++) {
		for (long x = 0; x < imagenMapa->getWidth(); x++) {
			if (y > imagenMapa->getHeight() * .5f) {
				if (x > imagenMapa->getWidth() * .5f) {
					datos[pos++] = 1;
					datos[pos++] = 0;
					datos[pos++] = 0;
					datos[pos++] = 1;
				} else {
					datos[pos++] = 0;
					datos[pos++] = 1;
					datos[pos++] = 0;
					datos[pos++] = 1;
				}
			} else {
				if (x > imagenMapa->getWidth() * .5f) {
					datos[pos++] = 0;
					datos[pos++] = 1;
					datos[pos++] = 1;
					datos[pos++] = 1;
				} else {
					datos[pos++] = 1;
					datos[pos++] = 1;
					datos[pos++] = 0;
					datos[pos++] = 1;
				}
			}

		}
	}/**/
	

	

	/*long pos2 = 0;
	for (float y = 0; y < lY; y++) {
		for (float x = 0; x < lX; x++) {
			if (x < 40) {
				if (y < 40) {
					tail[pos2++] = 0;
					tail[pos2++] = 1;
					tail[pos2++] = 0;
					tail[pos2++] = 1;
				} else {
					tail[pos2++] = 0;
					tail[pos2++] = 1;
					tail[pos2++] = 1;
					tail[pos2++] = 1;
				}
			} else {
				if (y < 40) {
					tail[pos2++] = 0;
					tail[pos2++] = 1;
					tail[pos2++] = 1;
					tail[pos2++] = 1;
				} else {
					tail[pos2++] = 0;
					tail[pos2++] = 0;
					tail[pos2++] = 1;
					tail[pos2++] = 1;
				}
			}
		}
	}/**/

	/*for (long x = 0; x < Screen::getWidth()-10; x++) {
		datos[pos++] = 0;
		datos[pos++] = 0;
		datos[pos++] = 1;
		datos[pos++] = 1;

	}*/

	/*cubo = Renderable::createRenderable<renderable::Cube>();
	cubo->setPosition((500.f / Screen::getWidth()) - 1, 1, 0);
	cubo->setRotation(0, 0, 0);
	cubo->setSize(1.f);
	///cubo->pX = (500.f / Screen::getWidth())-1;
	//cubo->pY = 0+1; //500.f / Screen::getHeight();
	//cubo->pZ = 1-1;
	//cubo->rX = 0;
	//cubo->rY = 0;
	//cubo->rZ = 0;
	//cubo->l = 1;
	cubo->r = 1;
	cubo->g = 0;
	cubo->b = 0;/**/
	/*renderable::Cube *cubo2 = Renderable::createRenderable<renderable::Cube>();
	cubo2->pX = 500.f / Screen::getWidth();
	cubo2->pY = 200.f / Screen::getHeight();
	cubo2->pZ = 100 / 100;
	cubo2->rX = 0;
	cubo2->rY = 0;
	cubo2->rZ = 0;
	cubo2->l = 1;
	cubo2->r = 0;
	cubo2->g = 1;
	cubo2->b = 0;/**/
}

void Minecraft::destroy(){
}

/*renderable::Img* Minecraft::cogerMapa() {
	return mapas[0];
}/**/

