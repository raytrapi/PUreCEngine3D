#ifndef __INTERFACE_COMPONENT
#define __INTERFACE_COMPONENT
#include "../../src/component.h"
#include "../../src/transform.h"
#include "../../src/exportar.h"
#include "../../../modules/src/module.h"
#include "../../../modules/graphic/motor.h"
#include "../../../utilidades/math/math.h"
//extern class InterfaceComponent;
struct ControlInterfaz {
	//TODO: Tendríamos que tener controles independientes
	enum TYPE {
		IMAGE,
		TEXT
	};

	//friend class InterfaceComponent;
	TYPE tipo = IMAGE;
	float* img=0; 
	std::string ruta="";
	unsigned int idTextura=0;
	///Extra
	float densidad=16.f;
	int wG=100;
	int hG=100;
	int octavos = 8;
	float persistencia = 0;
	float agua = 0;
	int semilla = -1;

	//Para el control de texto
	char* texto = 0;
	int longitudTexto;

	std::vector<std::tuple<float,float,float,float,float>> colores;
	void insertColor(float limit, float r, float g, float b, float a);
	ControlInterfaz() {}
	ControlInterfaz(TYPE tipo, float* img, int ancho, int alto) :
		tipo(tipo), img(img), ancho(ancho), alto(alto) {recalcule();}
	//ControlInterfaz(ControlInterfaz &c);
	~ControlInterfaz();
	void setPos(int xp, int yp) { x = xp; y = yp; recalcule(); };
	void setSize(int w, int h) { ancho = w; alto = h; recalcule(); };

	std::tuple<int, int> getPos() { return { x, y}; };
	std::tuple<int, int> getSize() { return { ancho, alto }; };
	bool isOver() { return encima; };
	int buttonPressed() { if (encima) { return botonPulsado; }; return -1; };
	void setOver(int xp, int yp, int buttonPres);

	void setText(char* texto,int length=0);
private:
	void recalcule();
	int ancho=0;
	int alto=0;
	int x=0;
	int y=0;
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	bool encima = false;
	int botonPulsado = -1;
};
class EXPORTAR_COMPONENTE InterfaceComponent : public Component {
	friend class modules::graphics::Graphic;
private:
	unsigned int vao = 0; //Array de vertices -> Apunta a un buffer
	unsigned int vbo = 0; //Buffer de vertices
	unsigned int ebo = 0; //Indice de vertices -> Indica como se lee el buffer
	unsigned int idTextura = 0;
	unsigned int shaderVertex = 0;
	unsigned int shaderFragment = 0;
	unsigned int shaderProgram = 0;
	float* imagen=0;
	unsigned int dimension[2]{ 0,0 };
	float proporcionX;
	float proporcionY;
	/*unsigned int* getVAO() { return &vao; };
	unsigned int* getEBO() { return &ebo; };
	unsigned int* getPrgram() { return &shaderProgram; };
	unsigned int* getIdTexture() { return &idTextura; };/**/
	void crearInterfaz();

	void redimImage(unsigned int ancho, unsigned int alto);
	void loadImageGraphic();

	//imagen, ancho, alto, x, y, ruta
	//std::vector<std::tuple<float*, int, int, int, int, std::string, unsigned int>> controles;
	std::vector<ControlInterfaz> controles;
	void loadImageControl(const char* ruta, int id, bool loadMemory);
	void refreshControls();
	float* resizeImage(const float* inputImage, int inputWidth, int inputHeight, int outputWidth, int outputHeight);
	int handleOnResize = -1;



	float* generateMapColor(int width, int height, int octetos, int aleatorio, std::vector<std::tuple<float, float, float, float, float>> colors);
	float* generatePerlinNoise(int width, int height, int octetos, int aleatorio, int wG, int hG, float density, float persistencia, float agua);
	/*float* generatePerlinNoise(int width, int height, int octetos);
	float* perlinOctave2D(float* wave, float frequency, float amplitude, int width, int height);
	float interpolateBilinear(int x1, int y1, int x2, int y2, float v1, float v2, float v3, float v4, int tx, int ty);
	float interpolateLinear(int x1, int y1, int x2, int y2);
	
	
	float perlin(float x, float y);/**/
	float dotGridGradient(int ix, int iy, float x, float y);
	float lerp(float a, float b, float t);
protected:
	bool interfazImGUI_C(ImGuiContext* imgui);
	int saveState_interno(std::vector<unsigned char>* data, bool withID = false);
	void restoreState_interno(std::vector<unsigned char>* data = 0, bool withID = false, int pos = -1);
public:
	InterfaceComponent(Entity* e, modules::graphics::Graphic* g, Component* p = NULL) :Component(e, g, p) { crearInterfaz(); };
	virtual ~InterfaceComponent();
	unsigned int getShaderProgram() { return shaderProgram; }
	unsigned int getVAO() { return vao; }
	unsigned int getEBO() { return ebo; }
	unsigned int getIdTexture() { return idTextura; }
	TYPE_OBJECT_SERIALIZABLES getType() { return TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_INTERFACE; };


	bool controlMouse(int x, int y, int buttonPress);


	

};
#endif // !__INTERFACE_COMPONENT
