#include "interfaceComponent.h"
#include <constantes.h>
#include <entity.h>

#include <../../../modules/resources/resource.h>


InterfaceComponent::~InterfaceComponent() {
	//DBG("Borro cámara");
	/*if (transformada) {
		delete transformada;
	}/**/

	if (imagen) {
		delete[] imagen;
	}
	if (handleOnResize >= 0) {
		Screen::removeOnResize(handleOnResize);
	}
}
void InterfaceComponent::loadImageControl(const char* ruta, int id, bool loadMemory) {
	auto resource = Module::get< modules::resources::Resource>();
	auto recurso = resource->loadImage(ruta, false);
	float* imTemp = std::get<0>(recurso);
	auto [controlAncho, controlAlto] = controles[id].getSize();
	if ((controlAncho != std::get<1>(recurso) || controlAlto != std::get<2>(recurso)) && controlAncho !=0 && controlAlto !=0) {
		imTemp = resizeImage(imTemp, std::get<1>(recurso), std::get<2>(recurso), controlAncho, controlAlto);
		std::get<1>(recurso) = controlAncho;
		std::get<2>(recurso) = controlAlto;
		delete[] std::get<0>(recurso);
		
	}
	if (std::get<0>(recurso) != 0) {
		if (controles[id].img != 0) {
			delete[]controles[id].img;
		}
		controles[id].img = imTemp;
		auto anchoImagen = std::get<1>(recurso);
		auto altoImagen = std::get<2>(recurso);
		controles[id].setSize(anchoImagen, altoImagen);
		
		auto l= std::get<3>(recurso);
		controles[id].ruta = std::string(ruta);
		if (loadMemory) {
			graphic->addTexture(imTemp, l, anchoImagen, altoImagen, controles[id].idTextura);
		}
		refreshControls();
	}
}
void InterfaceComponent::refreshControls() {
	int l = dimension[0] * dimension[1] * 4;
	//Se podría optimizar si conocemos donde no se ha de pintar
	for (int i = 0; i < l; ) {
		imagen[i++] = 0.0f;
		imagen[i++] = 0;
		imagen[i++] = 0;
		imagen[i++] = 0.0f;
		
	}
	for (auto itr = controles.begin(); itr != controles.end();itr++) {
		auto control = &(*itr);
		auto datos = control->img;
		if (datos == 0) {
			continue;
		}
		auto [ancho, alto] = control->getSize();
		auto [posX, posY] = control->getPos();
		
		//int posYActual = posY;
		//int posXActual = posX;
		int posActual = (posY * dimension[0] + posX)*4;
		int posDatoImagen = 0;
		int maxImagen = l - 3;
		for (int y = 0; y < alto; y++) {
			int recorridoX = 0;
			for (int x = 0; x < ancho; x++) {
				if (posActual > 0 && 
					(x+posX)< dimension[0] && (x+posX)>=0 &&
					(y+posY)< dimension[1] && (y+posY)>=0 && posDatoImagen<maxImagen) {
					//Estemos saliendo del área de ventana
					//TODO: Ahora no se controla
					/*
					R = (R1 * a1 / 255) + (R2 * a2 * (255 - a1) / (255^2))
					G = (G1 * a1 / 255) + (G2 * a2 * (255 - a1) / (255^2))
					B = (B1 * a1 / 255) + (B2 * a2 * (255 - a1) / (255^2))
					Alpha = a1 + (a2 * (255 - a1) / 255)
					/**/

					float aT = datos[posDatoImagen + 3];
					//if (aT != 1.0f) {
						float bT = imagen[posActual + 3];
						float alpha_1 = 1.0f - aT;
						float alpha0 = aT + bT * (alpha_1);
						float a = datos[posDatoImagen];
						float b = imagen[posActual];
						//imagen[posActual] = (a * aT) + (b  * alpha_1) ; //r
						imagen[posActual] = (a * aT) + (b * bT * alpha_1); //r
						posActual++; posDatoImagen++;
						a = datos[posDatoImagen];
						b = imagen[posActual];
						//imagen[posActual] = (a * aT) + (b * alpha_1); //g
						imagen[posActual] = (a * aT) + (b * bT * alpha_1); //g
						posActual++; posDatoImagen++;
						a = datos[posDatoImagen];
						b = imagen[posActual];
						//imagen[posActual] = (a * aT) + (b * alpha_1); //b
						imagen[posActual] = (a * aT) + (b * bT * alpha_1); //b
						posActual++; posDatoImagen++;
						//a = datos[posDatoImagen];
						//b = imagen[posActual];
						imagen[posActual] = alpha0; //a
						posActual++; posDatoImagen++;
					/* } else {
						imagen[posActual] = datos[posDatoImagen]; //r
						posActual++; posDatoImagen++;
						imagen[posActual] = datos[posDatoImagen]; //g
						posActual++; posDatoImagen++;
						imagen[posActual] = datos[posDatoImagen]; //b
						posActual++; posDatoImagen++;
						imagen[posActual] = datos[posDatoImagen]; //a
						posActual++; posDatoImagen++;
					}/**/
					recorridoX++;
				} else {
					posActual+=4;
					posDatoImagen += 4;
					recorridoX++;
				}
			}
			posActual += ((dimension[0] - recorridoX) * 4);
		}
	}/**/
	loadImageGraphic();
}

float* InterfaceComponent::resizeImage(const float* inputImage, int inputWidth, int inputHeight, int outputWidth, int outputHeight) {
	//TODO: Cambiar esto para que coja el limite. Si es menos de 0 pondrá 0 y si es más de límite superior pondrá ese valor
	if (outputWidth <= 0 || outputWidth > 2000 || outputHeight <= 0 || outputHeight >= 2000) {
		outputWidth = inputWidth;
		outputHeight = inputHeight;
	}
	float * outputImage=new float[outputWidth * outputHeight*4];

	for (int y = 0; y < outputHeight; ++y) {
		for (int x = 0; x < outputWidth; ++x) {
			float srcX = x * (float)(inputWidth) / (float) outputWidth;
			float srcY = y * (float)inputHeight / (float)outputHeight;

			int x0 = (int)srcX;
			int x1 = x0 + 1;
			if (x1 > inputWidth - 1) {
				x1 = inputWidth - 1;
			};

			int y0 = (int)srcY;
			int y1 = y0 + 1;
			if (y1 > inputHeight - 1) {
				y1 = inputHeight - 1;
			};

			float xFraction = srcX - x0;
			float yFraction = srcY - y0;

			// Interpolación bilineal
			for (int c = 0; c < 4; ++c) {  // RGBA channels
				float topInterpolation = (1 - xFraction) * inputImage[(y0 * inputWidth + x0) * 4 + c] + xFraction * inputImage[(y0 * inputWidth + x1) * 4 + c];
				float bottomInterpolation = (1 - xFraction) * inputImage[(y1 * inputWidth + x0) * 4 + c] + xFraction * inputImage[(y1 * inputWidth + x1) * 4 + c];

				outputImage[(y * outputWidth + x) * 4 + c]= (1 - yFraction) * topInterpolation + yFraction * bottomInterpolation;
			}
		}
	}

	
	return outputImage;
}
bool InterfaceComponent::interfazImGUI_C(ImGuiContext* imgui) {
	//ImGui::SetCurrentContext(imgui);
	ImGui::TableNextRow();
	ImGui::TableNextColumn();
	ImGui::Text(U8(Dimensión));
	ImGui::TableNextColumn();
	float dimension[2];
	dimension[0] = 0;
	dimension[1] = 0;
	ImGui::DragFloatN_Colored("dimension", dimension,2, 0.05f);

	for (int idControl = 0; idControl < controles.size();idControl++) {
		auto control = &controles[idControl];//Trabajamos con direcciones para evitar crear un constructor de copia

		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(U8(Control));
		ImGui::TableNextColumn();
		{
			ImGui::BeginTable("##d",2);

			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text(U8(Tamaño));
			ImGui::TableNextColumn();
			int tam[2];
			std::tie(tam[0],tam[1])=control->getSize();
			bool conCambio = false;
			if (ImGui::DragInt2("##tam", tam,1,0,2000)) {
				
				if (controles[idControl].img != 0 && controles[idControl].ruta!="") {
					controles[idControl].setSize(tam[0], tam[1]);
					loadImageControl(controles[idControl].ruta.c_str(), idControl, false);
				} else {
					if (controles[idControl].img != 0) {
						auto [w, h] = controles[idControl].getSize();
						float* f = resizeImage(controles[idControl].img, w, h, tam[0], tam[1]);
						float* f2 = controles[idControl].img;
						controles[idControl].img = f;
						delete[] f2;
					}
					controles[idControl].setSize(tam[0], tam[1]);
				}
				refreshControls();
				conCambio = true;
			};

			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text(U8(Posición));
			ImGui::TableNextColumn();
			int pos[2];
			std::tie(pos[0],pos[1])= control->getPos();
			//bool conCambio = false;
			if (ImGui::DragInt2("##pos", pos)) {
				controles[idControl].setPos(pos[0], pos[1]);
				refreshControls();
				conCambio = true;
			};
			switch (control->tipo) {
				case ControlInterfaz::IMAGE:
				{
					{
						ImGui::TableNextRow();
						ImGui::TableNextColumn();
						ImGui::Text(U8(Datos));
						ImGui::TableNextColumn();
						bool cambio = false;
						cambio = cambio || ImGui::DragFloat("den", &controles[idControl].densidad, 0.01F, 1.0f);
						cambio = cambio || ImGui::DragInt("w", &controles[idControl].wG, 1.0f, 1);
						cambio = cambio || ImGui::DragInt("h", &controles[idControl].hG, 1.0f, 1);

					}
					{
						ImGui::TableNextRow();
						ImGui::TableNextColumn();
						ImGui::Text(U8(Octavas));
						ImGui::TableNextColumn();
						int o = control->octavos;
						if (ImGui::DragInt("##oct", &o, 1.0, 0.f, 50.f)) {
							controles[idControl].octavos = o;
						}
						ImGui::DragFloat("per", &controles[idControl].persistencia, 0.01f, 0);
						ImGui::DragFloat("agu", &controles[idControl].agua, 0.01f, 0);
					}
					{
						ImGui::TableNextRow();
						ImGui::TableNextColumn();
						ImGui::Text(U8(Semilla));
						ImGui::TableNextColumn();
						int o = control->semilla;
						if (ImGui::DragInt("##semilla", &o, 1.0, -1.f)) {
							controles[idControl].semilla = o;
						}
					}

					char* eLimite = new char[] {'#', '#', '0', '0', 'l', 'i', 'm', 'i', 't', 'e', 'c', 'o', 'l', 'o', 'r', '\0'};
					char* eColor = new char[] {'#', '#', '0', '0', 'c', 'o', 'l', 'o', 'r', '\0'};
					int iColor = 0;
					for (auto itrColor = controles[idControl].colores.begin(); itrColor != controles[idControl].colores.end(); itrColor++) {


						char id = '0' + (iColor / 10);
						eLimite[2] = id;
						eColor[2] = id;
						id = '0' + (iColor % 10);
						eLimite[3] = id;
						eColor[3] = id;
						ImGui::TableNextRow();
						ImGui::TableNextColumn();
						ImGui::Text(U8(Color));
						ImGui::TableNextColumn();
						float l = std::get<0>(*itrColor);
						if (ImGui::DragFloat(eLimite, &l, 0.01, 0.f, 1.f)) {
							std::get<0>(*itrColor) = l;
							//controles[idControl].reordenarColores();
						}
						float c[4] = { std::get<1>(*itrColor), std::get<2>(*itrColor), std::get<3>(*itrColor), std::get<4>(*itrColor) };
						if (ImGui::ColorEdit4(eColor, c)) {
							std::get<1>(*itrColor) = c[0];
							std::get<2>(*itrColor) = c[1];
							std::get<3>(*itrColor) = c[2];
							std::get<4>(*itrColor) = c[3];
						}
						iColor++;
					}
					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text(U8(Colores));
					ImGui::TableNextColumn();
					if (ImGui::Button("Nuevo Color")) {
						controles[idControl].colores.push_back({ 0,0,0,0,1.0 });
					}


					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text(U8(Perlin));
					ImGui::TableNextColumn();
					auto [anchoMapa, altoMapa] = controles[idControl].getSize();
					if (ImGui::Button("Generar mapa")) {
						//float * imagen=generatePerlinNoise(controles[idControl].ancho, controles[idControl].alto,8);
						float* imagen = generateMapColor(anchoMapa, altoMapa, controles[idControl].octavos, controles[idControl].semilla, controles[idControl].colores);
						float* imagen2 = controles[idControl].img;
						controles[idControl].img = imagen;
						if (imagen2 != 0) {
							delete[] imagen2;
						}
						refreshControls();
					}
					if (ImGui::Button("Generar mapa Grises")) {
						float* imagen = generatePerlinNoise(anchoMapa, altoMapa, controles[idControl].octavos, controles[idControl].semilla, controles[idControl].wG, controles[idControl].hG, controles[idControl].densidad, controles[idControl].persistencia, controles[idControl].agua);
						//float* imagen = generateP(controles[idControl].ancho, controles[idControl].alto, controles[idControl].octavos, controles[idControl].semilla, controles[idControl].colores);
						float* imagen2 = controles[idControl].img;
						controles[idControl].img = imagen;
						if (imagen2 != 0) {
							delete[] imagen2;
						}
						refreshControls();
					}
					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text(U8(Fichero));
					ImGui::TableNextColumn();
					/*char* f = new char[200];
					auto l = std::get<5>(control).size();
					for (int i = 0; i < l; i++) {
						f[i] = std::get<5>(control)[i];
					}
					f[l] = '\0';
					if (ImGui::InputText("fichero", f, 200)) {
						loadImageControl(f, idControl);

					};

					delete[]f;/**/
					//if (std::get<6>(control) != 0) {
					if (control->isOver()) {
						ImGui::Text("Encima");
					}
					ImGui::Image((void*)(intptr_t)control->idTextura, ImVec2(100, 100), ImVec2(0, 1.0f), ImVec2(1.0f, 0));
					if (!ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::BeginDragDropTarget()) {
						if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DRAG_IMAGEN")) {
							if (payload->DataSize == sizeof(DragFile)) {
								auto datos = *(DragFile*)payload->Data;
								controles[idControl].idTextura = datos.idImagen;

								loadImageControl((Global::getInstance()->getPathRoot() + "/" + datos.path + "/" + datos.name).c_str(), idControl, false);

								//refreshControls();
							}
						}

						ImGui::EndDragDropTarget();
					}
					//}
				}
				break;
				case ControlInterfaz::TEXT: 
				{
					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text(U8(Texto));
					ImGui::TableNextColumn();
					char* bufTexto = new char[1000];
					if (control->texto){
						for (int i = 0; i < control->longitudTexto; i++) {
							bufTexto[i] = control->texto[i];
						}
					}
					bufTexto[control->longitudTexto] = '\0';
					if (ImGui::InputText("##texto", bufTexto, 1000)) {
						//TODO: Estamos creando espacios de memoria en cada paso, sería mejor tener único buffer.
						controles[idControl].setText(bufTexto);
						
					};
				}
				break;
			}
			ImGui::EndTable();
		}
	}


	ImGui::TableNextRow();
	ImGui::TableNextColumn();
	ImGui::Text(U8(Acción));
	ImGui::TableNextColumn();
	if (ImGui::Button("Nuevo Control")) {
		controles.push_back({ ControlInterfaz::TYPE::IMAGE,0,0,0 });
	}
	return true;
}




int InterfaceComponent::saveState_interno(std::vector<unsigned char>* data, bool withID) {
	
	int longitud = Serializer::serialize(data, (int)TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_INTERFACE);
	longitud += Serializer::serialize(data, ((int)controles.size()));
	for (auto control : controles) {
		auto [w, h] = control.getSize();
		auto [x, y] = control.getPos();
		longitud+=Serializer::serialize(data, control.tipo, x, y, w, h, control.ruta.c_str());
		longitud += Serializer::serialize(data, control.octavos, ((int)control.colores.size()));
		for (auto color : control.colores) {
			longitud += Serializer::serialize(data, std::get<0>(color), std::get<1>(color), std::get<2>(color), std::get<3>(color), std::get<4>(color));
		}
		
	};
	return longitud;
};
void InterfaceComponent::restoreState_interno(std::vector<unsigned char>* data, bool withID, int pos) {
	//transformada->restoreState(data, withID, pos);
	if (data != 0) {
		Deserializer::stackBytes(data);
	}
	int l = 0;
	Deserializer::deserialize(&l);
	for (int i = 0; i < l; i++) {
		ControlInterfaz c;
		int x;
		int y;
		int w;
		int h;
		Deserializer::deserialize(&c.tipo, &x, &y, &w, &h);
		c.setSize(w, h);
		c.setPos(x, y);
		char* s = 0;
		Deserializer::deserialize(&s);
		c.ruta = std::string(s);
		
		delete[]s;
		Deserializer::deserialize(&c.octavos);
		int l2 = 0;
		Deserializer::deserialize(&l2);
		for (int j = 0; j < l2; j++) {
			std::tuple<float, float, float, float, float> nivel;
			Deserializer::deserialize(&std::get<0>(nivel), &std::get<1>(nivel), &std::get<2>(nivel), &std::get<3>(nivel), &std::get<4>(nivel));
			c.colores.push_back(nivel);
		}

		controles.push_back(c);
		if (c.ruta.length() > 1) {
			loadImageControl(c.ruta.c_str(), i, false);
		}
	}
	if (data != 0) {
		Deserializer::unstackBytes();
	}
};

void InterfaceComponent::loadImageGraphic(){
	if (idTextura == 0) {
		//graphic->releaseTexture(idTextura);
	}
	graphic->addTexture(imagen, dimension[0]*dimension[1]*4, dimension[0], dimension[1], idTextura);

}
void InterfaceComponent::redimImage(unsigned int ancho, unsigned int alto) {
	/*float* imagenAnterior = imagen;
	
	int l = ancho * alto * 4;
	imagen = new float[l];
	

	//TODO: Copiar contenido de la imagen anterior



	if (imagenAnterior != 0) {
		delete[]imagenAnterior;
	}/**/
	dimension[0] = ancho;
	dimension[1] = alto;
	proporcionX = 2.f;
	proporcionY = 2.f;
	if (imagen != 0) {
		delete[]imagen;
		imagen = 0;
	}
	imagen = new float[dimension[0]* dimension[1]*4];
	refreshControls();
	
}
void InterfaceComponent::crearInterfaz() {
	handleOnResize = Screen::onResize([&](int ancho, int alto) {
		this->redimImage(ancho, alto);
	});
	//Obtener el tamaño de ventana
	//if (dimension[0] == 0 || dimension[1] == 0) {
		dimension[0] = Screen::getWidth();
		dimension[1] = Screen::getHeight();


		//proporcionX = (dimension[0] / Screen::getWidth()) * 2 ;
		//proporcionY = (dimension[1] / Screen::getHeight()) * 2;
		proporcionX = 2.f;
		proporcionY = 2.f;
		if (imagen != 0) {
			delete[]imagen;
		}
		imagen = new float[dimension[0] * dimension[1] * 4];

	//}
	float datos[20]{
	-1.0f, 1.0f - proporcionY, 0.0f,				0.0f, 1.0f,
		-1.0f + proporcionX, 1.0f - proporcionY, 0.0f,	1.0f, 1.0f,
		-1.0f + proporcionX, 1.0f, 0.0f,				1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,								0.0f, 0.0f
	};/**/
	/*float datos[20]{
		-0.5f, 0.5f - proporcionY, 0.0f,				0.0f, 1.0f,
		-0.5f + proporcionX, 0.5f - proporcionY, 0.0f,	1.0f, 1.0f,
		-0.5f + proporcionX, 0.5f, 0.0f,				1.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,								0.0f, 0.0f
	};/**/
	graphic->generateRectangleInterface(datos, &vao, &vbo, &ebo);
	//TODO: Shaders como bytes *
	shaderVertex = graphic->loadShader("shaders/Interfaz/vertex.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
	shaderFragment = graphic->loadShader("shaders/Interfaz/fragment.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
	std::vector<unsigned int> shaders;
	shaders.push_back(shaderVertex);
	shaders.push_back(shaderFragment);
	shaderProgram = graphic->compileShader(&shaders);
	

	



};
bool InterfaceComponent::controlMouse(int x, int y, int buttonPress) {
	for (auto itrc = controles.begin(); itrc != controles.end();itrc++) {
		itrc->setOver(x, y, buttonPress);
	}
	return false;
}


void ControlInterfaz::setOver(int xp, int yp, int buttonPress) {
	encima = (xp >= x1 && xp <= x2 && yp >= y1 && yp <= y2);
	botonPulsado = buttonPress;

};
void ControlInterfaz::recalcule() {
	x1 = x;// -ancho / 2;
	y1 = y;// -alto / 2;
	x2 = x1 + ancho;
	y2 = y1 + alto;
};


////******/////
// PERLIN
/*float InterfaceComponent::interpolateLinear(int x1, int y1, int x2, int y2) {
	return ((x2 - x1) * (y2 - y1) / (x2 - x1)) + y1;

}
float InterfaceComponent::interpolateBilinear(int x1, int y1, int x2, int y2, float v1, float v2, float v3, float v4, int tx, int ty) {
	float area_v1 = (float)abs((tx - x1) * (ty - y1)) * v4;
	float area_v2 = (float)abs((tx - x2) * (ty - y1)) * v3;
	float area_v3 = (float)abs((tx - x1) * (ty - y2)) * v2;
	float area_v4 = (float)abs((tx - x2) * (ty - y2)) * v1;
	float area_total = (x2 - x1) * (y2 - y1);
	float sum = (area_v1 + area_v2 + area_v3 + area_v4);
	if (area_total != 0 && sum != 0) {
		return sum / area_total;
	} else {
		return 0;
	}
}
float* InterfaceComponent::perlinOctave2D(float * wave, float frequency, float amplitude, int width, int height) {
	int step_length = floor((float)width / frequency);
	if (step_length <= 0) {
		step_length = 1;
	}
	//DBG("step %", step_length);

	int l = width * height;
	
	float * wave2 = new float[l];
	for (int i = 0; i < l; i++) {
		wave2[i] = 0.0f;
	}

	//int pos = 0;
	for (int y = 0; y <= height; y+=step_length){
		for (int x = 0; x <= width; x+= step_length){
			int posX = x < width ? x : width - 1;
			int posY = y < height ? y : height - 1;
//			if (y<height && x<width) {
			float a1 = (float)std::rand();
			float aleatorio = ( a1/ (float)RAND_MAX);
			wave2[posY * width + posX] = (amplitude / 2.f) - (aleatorio * amplitude);
//			}
			
			//Interpolation between nodes
			if (y >= step_length && x >= step_length)	{
				int y1 = y - (step_length);
				int y2 = y;
				int x1 = x - (step_length);
				int x2 = x;
				if (x1 >= width) {
					x1 = width-1;
				}
				if (x2 >= width) {
					x2 = width-1;
				}
				if (y1 >= height) {
					y1 = height-1;
				}
				if (y2 >= height) {
					y2 = height-1;
				}
				float v1= wave2[x1 + y1 * width];
				float v2= wave2[x2 + y1 * width];
				float v3= wave2[x1 + y2 * width];
				float v4= wave2[x2 + y2 * width];
				for (int a = y - (step_length); a < y; a++)	{
					for (int b = x - (step_length); b < x; b++)	{
						wave2[a*width+b] = interpolateBilinear(x1, y1, x2, y2, v1, v2, v3, v4, b, a);
					}
				}
			}
			
		}
	}
	if (wave == 0) {
		wave = new float[l];
		for (int i = 0; i < l; i++) {
			wave[i] = wave2[i];
		}
	} else {
		for (int i = 0; i < l; i++) {
			wave[i] +=wave2[i];
			
		}
	}
	delete[] wave2;
	return wave;
}

float* InterfaceComponent::generatePerlinNoise(int width, int height, int octetos) {
	std::srand(100);// std::time(nullptr));
	//DBG("aleatorio %", std::rand());
	if (width <= 0 || height <=0) {
		return 0;
	}
	int size = width * height;
	float* img = new float[size * 4];
	int pos = 0;
	for (int i = 0; i < size; i++) {
		img[pos++] = 0.0f;
		img[pos++] = 0.0f;
		img[pos++] = 0.0f;
		img[pos++] = 1.0f;
	}
	float* valores = perlinOctave2D(0, 1.0f, 256.0f, width, height);
	for (int octeto = 1; octeto < octetos; octeto++) {
		
		float actual = powf(2, octeto);
		valores= perlinOctave2D(valores, actual, 256.0f/ actual, width, height);
		
	}
	int i = 0;
	int j = 0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float gray = floor(128.0f + valores[j]) / 255.f;
			img[i++] = gray;
			img[i++] = gray;
			img[i++] = gray;
			img[i++] = 1.0f;
			j++;
			//i++;
		}
	}
	delete[] valores;
	return img;
	// Inicializa el generador de números aleatorios con una semilla
	std::srand(std::time(nullptr));

	// Aquí deberías implementar la generación de ruido de Perlin en tonos de gris
	 i=0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float gray = (perlin(static_cast<float>(x) / width, static_cast<float>(y) / height)+1.0f)*0.5f;
			// Asigna el valor de escala de grises a los canales rojo, verde y azul
			img[i ] = gray;     // Canal rojo
			img[i + 1] = 0; // Canal verde
			img[i + 2] = 0; // Canal azul

			// El canal alfa se mantiene constante (puedes ajustarlo según tus necesidades)
			img[i + 3] = 1.f; // Canal alfa (completamente opaco)
			i+=4;
		}
	}
	

	return img;
}/**/

float* InterfaceComponent::generatePerlinNoise(int width, int height, int octetos, int aleatorio, int wG, int hG, float density, float persistencia, float agua) {
	if (width <= 0 || height <= 0) {
		return 0;
	}
	int size = width * height;
	float* img = new float[size * 4];
	//std::srand(seed >= 0 ? seed : std::time(nullptr));
	float* valores = Math::perlin2D(0,0,width, height,aleatorio, wG, hG, density,octetos,persistencia,agua);
	int i = 0;
	int j = 0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float valor = valores[j];

			img[i++] = valor;
			img[i++] = valor;
			img[i++] = valor;
			img[i++] = 1.f;
			j++;
			//i++;
		}
	}
	delete[]valores;
	return img;
}
float* InterfaceComponent::generateMapColor(int width, int height, int octetos, int seed, std::vector<std::tuple<float, float, float, float, float>> colors) {
	//std::srand(100);// std::time(nullptr));
	//DBG("aleatorio %", std::rand());
	if (width <= 0 || height <= 0) {
		return 0;
	}
	if (octetos < 1) {
		octetos = 1;
	}
	int size = width * height;
	float* img = new float[size * 4];
	/*float* valores = perlinOctave2D(0, 1.0f, 256.0f, width, height);
	for (int octeto = 1; octeto < octetos; octeto++) {
		float actual = powf(2, octeto);
		valores = perlinOctave2D(valores, actual, 256.0f / actual, width, height);
	}/**/
	std::srand(seed >= 0 ? seed : std::time(nullptr));
	/*float* valores2 = perlinOctave2D(0, 1.0f, 256.0f, width, height);
	//DBG("aleatorio %", std::rand());
	for (int octeto = 1; octeto < octetos; octeto++) {

		float actual = powf(2, octeto);
		valores2= perlinOctave2D(valores2, actual, 256.0f / actual, width, height);

	}/**/
	//float* valores = Math::perlin2D(0,0,width, height, octetos, 256.0f, seed);
	float* valores = Math::perlin2D(0, 0, width, height, seed);
	//delete[]valores2;

	int i = 0;
	int j = 0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float valor = valores[j];

			
			std::tuple<float,float,float,float> colorBase = { valor,valor,valor,1.0f };
			if (colors.size() > 0) {
				colorBase = { std::get<1>(colors[0]),std::get<2>(colors[0]) ,std::get<3>(colors[0]) ,std::get<4>(colors[0]) };
				for (auto color : colors) {
					if (std::get<0>(color) < valor) {
						break;
					}
					colorBase = { std::get<1>(color),std::get<2>(color) ,std::get<3>(color) ,std::get<4>(color) };
				}
			}
			
			img[i++] = std::get<0>(colorBase);
			img[i++] = std::get<1>(colorBase);
			img[i++] = std::get<2>(colorBase);
			img[i++] = std::get<3>(colorBase);
			j++;
			//i++;
		}
	}
	delete[] valores;
	return img;
}







// Función para interpolar suavemente entre dos valores

float InterfaceComponent::lerp(float a, float b, float t) {
	return a + t * (b - a);
}

// Función para calcular el producto escalar entre un gradiente y un vector
float InterfaceComponent::dotGridGradient(int ix, int iy, float x, float y) {
	// Genera un vector aleatorio (gradiente) para la casilla (ix, iy)
	// Debes implementar una función que genere un gradiente para cada punto de la grilla
	// Aquí, simplemente se utiliza una función de ruido gaussiano como ejemplo
	float randomX = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f;
	float randomY = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f;

	// Calcula el vector desde el punto de la grilla hasta (x, y)
	float dx = x - static_cast<float>(ix);
	float dy = y - static_cast<float>(iy);

	// Calcula el producto escalar entre el gradiente y el vector
	return (dx * randomX + dy * randomY);
}

// Función para calcular el valor de ruido Perlin en una posición dada
/*float InterfaceComponent::perlin(float x, float y) {
	// Coordenadas de la esquina de la celda en la que se encuentra (x, y)
	int x0 = static_cast<int>(x);
	int x1 = x0 + 1;
	int y0 = static_cast<int>(y);
	int y1 = y0 + 1;

	// Fracción de (x, y) dentro de la celda
	float fracX = x - static_cast<float>(x0);
	float fracY = y - static_cast<float>(y0);

	// Interpola los valores de ruido en las esquinas de la celda
	float n0 = dotGridGradient(x0, y0, x, y);
	float n1 = dotGridGradient(x1, y0, x, y);
	float ix0 = lerp(n0, n1, fracX);

	n0 = dotGridGradient(x0, y1, x, y);
	n1 = dotGridGradient(x1, y1, x, y);
	float ix1 = lerp(n0, n1, fracX);

	// Interpola el valor interpolado en la dirección y
	return lerp(ix0, ix1, fracY);
}/**/


void ControlInterfaz::insertColor(float limit, float r, float g, float b, float a ) {
	if (limit > 1.f) {
		limit = 1.f;
	}
	if (limit < 0.f) {
		limit = 0.f;
	}
	auto iterador = colores.begin();
	while (iterador != colores.end()) {
		if (std::get<0>(*iterador) < limit) {
			colores.insert(iterador, { limit,r,g,b,a });
		}
	}
	colores.push_back({ limit,r,g,b,a });
}
ControlInterfaz::~ControlInterfaz() {
	if (img) {
		delete[]img;
	}
	if (texto) {
		delete[]texto;
	}
}
void ControlInterfaz::setText(char* text, int length) {
	if (texto) {
		delete[] texto;
	}

	int l = length;
	if (l <= 0) {
		l=strlen(text);
	}
	texto = new char[l + 1];
	for (int i = 0; i < l; i++) {
		texto[i] = text[i];
	}
	texto[l] = '\0';
}