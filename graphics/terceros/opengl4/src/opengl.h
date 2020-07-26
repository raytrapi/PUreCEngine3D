#ifndef __MOTORGL
#define __MOTORGL
#define GL_GLEXT_PROTOTYPES

#include <glad/gl.h>
//#include <gl/GLU.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../../imagenes/imagen.h"
#include "../../imagenes/png.h"
#include "../src/renderable/object.h"
#include "../src/renderable/pixel.h"
#include "../src/renderable/cube.h"
#include "../src/renderable/img.h"




//Luego quitaremos
#include "../../utilidades/global/mouse.h"
#include "../../utilidades/global/input.h"


#include <entity.h>
//#include <utilidades.h>
#include <log.h>
#include <module.h>
#include <motor.h>
#include <vector>
#include <string>
#include <fstream>
class  MotorGL:public modules::graphics::Graphic {
private:
		double ancho;
		double alto;
		GLFWwindow* window;
		
		std::vector<GLuint> shaders;
		static Input input;
		void inicializarLuz();
		void renderizarCubo(renderable::Cube *);
		void renderizarImagen(renderable::Img* img);

		
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
protected:
	float* points;
	bool derecha = true;

	void SetData();
public:
	MotorGL();
	~MotorGL();
	void renderizar();
	void renderizar(void *);
	bool inicializar(void * contexto, double ancho, double alto);
	char* nombre() { return (char*)"OPENGL 4"; };
		
	void ponerCamara(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);

	/*void newEntity(TYPE_ENTITY type, renderable::Object* object);
	const byte* loadShader(const char* path);
	int loadShader(const char* path, renderable::Shader::TYPE type, renderable::Object* object);
	int compileShader(renderable::Object* object);
	int compileShader(renderable::Object* object, int ps);*/
};
#endif // !__MOTORGL
