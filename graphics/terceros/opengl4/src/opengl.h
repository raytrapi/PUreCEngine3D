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
#include "entitygl4.h"
//#include <utilidades.h>
#include <log.h>
#include <module.h>
#include <motor.h>
#include "../../modules/tape/tape.h"
#include <vector>
#include <string>
#include <fstream>
#include <type_traits>
#include <log.h>

#include <map>
class  MotorGL:public modules::graphics::Graphic {
private:
		double ancho;
		double alto;
		GLFWwindow* window;

		//TODO: Posible fallo si necesitamos representar los elementos en orde
		std::map<Entity*, EntityGL4*> misEntidades;

		//std::vector<GLuint> shaders;
		static Input input;
		void inicializarLuz();
		void renderizarCubo(renderable::Cube *);
		void renderizarImagen(renderable::Img* img);

		
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void focus(GLFWwindow* window, int focused);
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

	void updateEntity(void* entity);
	//void addEntity(void* entity);
	void removeEntity(void* entity);
	void clearEntity(EntityGL4* entidad);
	void removeEntities();
	/*void newEntity(TYPE_ENTITY type, renderable::Object* object);*/

	//TODO: Optimizar la carga de Shader para que no se dupliquen
	const byte* loadShader(const char* path);
	int loadShader(const char* path, Graphics::Shader::TYPE_SHADER type);
	void reloadShader(const char* path, Graphics::Shader::TYPE_SHADER type, int idShader, int idProgram);
	int compileShader(std::vector<short>* ids);
	int compileShader(int ps);
	int compileShader(std::vector<short>*, void* entity);
	int compileShader(int ps, void* entity);



	static void closeWindow(GLFWwindow* window);
};
#endif // !__MOTORGL
