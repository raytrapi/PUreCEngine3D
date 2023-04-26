#ifndef __MOTORGL_4
#define __MOTORGL_4



#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024




#include "../../imagenes/imagen.h"
#include "../../imagenes/png.h"
#include "../src/renderable/object.h"
#include "../src/renderable/pixel.h"
#include "../src/renderable/cube.h"
#include "../src/renderable/img.h"
#include "../src/renderable/line.h"
#include "../src/renderable/text.h"



//Luego quitaremos
#include "../../utilidades/global/mouse.h"
#include "../../utilidades/global/input.h"

#include <entity.h>
#include <camera.h>
#include <renderable.h>
#include "entitygl4.h"
#include "imgui/interface.h"
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

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


#if defined(_MSC_VER)
 // Make MS math.h define M_PI
#define _USE_MATH_DEFINES
#endif

#include <math.h>
//extern class Input;

class  MotorGL:public modules::graphics::Graphic {
private:
		
		
		GLFWwindow* window;
		std::map< GLuint, std::tuple< GLuint, GLuint>> myLight;
		//GLuint mylightbuffer=0;
		//GLuint mylightbind = 0;
		
		//TODO: Posible fallo si necesitamos representar los elementos en orde
		std::map<Entity*, EntityGL4*> misEntidades;

		//std::vector<GLuint> shaders;
		
		void inicializarLuz();
		void renderizarCubo(renderable::Cube* cube);
		void renderizarImagen(renderable::Img* img);

		
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseMove_callback(GLFWwindow* window, double x, double y);
		static void mouseButtom_callback(GLFWwindow* window, int buttom, int action, int mods);
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void focus(GLFWwindow* window, int focused);
		
		Camera* camaraActual=NULL;

		//TODO: BORRAR
		//void pruebaCamara();
		//vec3 eye = { 3.f, 1.5f, 3.f };
		//vec3 center = { 0.f, 0.f, 0.f };
		//vec3 up = { 0.f, 1.f, 0.f };
		float eye[3]= {2.0f, 0.f, 3.f };//{ 0.f, 0.f, 2.f };
		float target[3] = { 0.0f, 0.0f, 0.0f };
		float up[3] = { 0.0f, 1.0f, 0.0f };
		//TODO: crear método par calcular la dimensión y la normal
		float f_t[3] = { eye[0] - target[0], eye[1] - target[1], eye[2] - target[2] };
		//float f_t[3] = { target[0] - eye[0], target[1] - eye[1], target[2] - eye[2] };
		
		//OJO puede ser todo 0;
		float f_dimension = 1/sqrtf(powf(f_t[0],2) + powf(f_t[1],2)+ powf(f_t[2],2));
		float axiZ[3] = { f_t[0] * f_dimension, f_t[1] * f_dimension, f_t[2] * f_dimension };
		
		//float s_t[3] = { f[1] * up[2] - f[2] * up[1], f[2] * up[0] - f[0] * up[2], f[0] * up[1] - f[1] * up[0] };
		/*float s_t[3] = { 
			axiZ[1] * up[2] - axiZ[2] * up[1], 
			axiZ[2] * up[0] - axiZ[0] * up[2], 
			axiZ[0] * up[1] - axiZ[1] * up[0] 
		};/**/
		float s_t[3] = {
			up[1] * axiZ[2] - up[2] * axiZ[1],
			up[2] * axiZ[0] - up[0] * axiZ[2],
			up[0] * axiZ[1] - up[1] * axiZ[0]
		};/**/
		float s_hipo = sqrtf(powf(s_t[0], 2) + powf(s_t[1], 2) + powf(s_t[2], 2));
		float s_dimension = (s_hipo!=0)?1 / s_hipo:0;
		//OJO puede ser todo 0;
		float axiX[3] = { s_t[0] * s_dimension, s_t[1] * s_dimension, s_t[2] * s_dimension };

		//float t[3] = { s[1] * f[2] - s[2] * f[1], s[2] * f[0] - s[0] * f[2], s[0] * f[1] - s[1] * f[0] };
		/*float axiY[3] = {
			axiX[1] * axiZ[2] - axiX[2] * axiZ[1],
			axiX[2] * axiZ[0] - axiX[0] * axiZ[2],
			axiX[0] * axiZ[1] - axiX[1] * axiZ[0]
		};/**/
		float axiY[3] = { 
			axiZ[1] * axiX[2] - axiZ[2] * axiX[1], 
			axiZ[2] * axiX[0] - axiZ[0] * axiX[2],
			axiZ[0] * axiX[1] - axiZ[1] * axiX[0] 
		};/**/


		//look_at
		float vista[16] = {
			axiX[0], axiY[0], axiZ[0], 0.f,
			axiX[1], axiY[1], axiZ[1], 0.f,
			axiX[2], axiY[2], axiZ[2], 0.f,

				((axiX[0] * -eye[0]) + (axiX[1] * -eye[1]) + (axiX[2] * -eye[2])),
				((axiY[0] * -eye[0]) + (axiY[1] * -eye[1]) + (axiY[2] * -eye[2])),
				((axiZ[0] * -eye[0]) + (axiZ[1] * -eye[1]) + (axiZ[2] * -eye[2])),
				1
		};/**/
		/*float vista[16] = {
			axiX[0], axiY[0], -axiZ[0], 0.f,
			axiX[1], axiY[1], -axiZ[1], 0.f,
			axiX[2], axiY[2], -axiZ[2], 0.f,

				((axiX[0] * -eye[0]) + (axiX[1] * -eye[1]) + (axiX[2] * -eye[2])),
				((axiY[0] * -eye[0]) + (axiY[1] * -eye[1]) + (axiY[2] * -eye[2])),
				((-axiZ[0] * -eye[0]) + (-axiZ[1] * -eye[1]) + (-axiZ[2] * -eye[2])),
				1
		};/**/
		/*float vista[16] = {
			1.00f, 0.00f, 0.00f, 0.00f,
			0.00f, 1.00f, 0.00f, 0.00f,
			0.00f, 0.00f, 1.00f, 0.00f,
			0.00f, 0.00f, 0.00f, 1.00f
		};*/
		
		float r2 = 1.00f;
		float l2 =-1.00f;
		float t2 = 1.00f;
		float b2 =-1.00f;
		
		float n2 = 1.00f; 
		float f2 =10.00f;

		/*float proyeccion[16] = {
			(2*n)/(r-l), 0.00f, (r+l)/(r-l), 0.00f,
			0.00f,(2*n)/(t-b), (t+n)/(t-b), 0.00f,
			0.00f, 0.00f, -(f+n)/(f-n), (-2*f*n)/(f-n),
			0.00f, 0.00f,-1.00f, 0.00f
		};/**/
		float y_fov = (65.f*0.5f) * (float)M_PI / 180.f;
		float aspect = 1.0f;//(float)(800 / 800);
		float const a = 1.f / tanf(y_fov);
		/*float proyeccion[16] = {
			a, 0.00f, 0.00f, 0.00f,
			0.00f, a, 0.00f, 0.00f,
			0.00f, 0.00f, -((f2 ) / (f2 - n2)), -1,
			0.00f, 0.00f,-((f2 * n2) / (f2 - n2)), 0.00f
		};/**/
		float proyeccion[16] = {
			a / aspect, 0.00f, 0.00f, 0.00f,
			0.00f, a, 0.00f, 0.00f,
			0.00f, 0.00f, -((f2 + n2) / (f2 - n2)), -1,
			0.00f, 0.00f,-((2.f * f2 * n2) / (f2 - n2)), 0.00f
		};/**/
		/*float proyeccion[16] = {
			(n) / (r), 0.00f, 0.00f, 0.00f,
			0.00f, n / t, 0.00f, 0.00f,
			0.00f, 0.00f, -1*((f + n) / (f - n)), 0,//(-2 * f * n) / (f - n),
			0.00f, 0.00f,-1.00f, 0.00f
		};*/
		float proyeccionOrto[16] = {
			2/(r2-l2), 0.00f, 0.00f, -(r2+l2)/(r2-l2),
			0.00f, 2/(t2-b2), 0.00f, -(t2+b2)/(t2-b2),
			0.00f, 0.00f, -2/(f2-n2), -(f2+n2)/(f2-n2),
			0.00f, 0.00f, 0.00f, 1.00f
		};

		struct nk_context* ctx;
		struct nk_font_atlas* atlas;
protected:
	float* points=NULL;
	bool derecha = true;
	unsigned int fbo=0;
	unsigned int rbo=0;

	
	

	bool inicializado = false;
	//InterfaceGL* interfaz = NULL;
	
	void SetData();

	void updateEntityLINE(RenderableComponent* render, EntityGL4* entidad, Entity* entity, TYPE_OPERATION type);
	void updateEntityIMG(RenderableComponent* render, EntityGL4* entidad, Entity* entity, TYPE_OPERATION type);
	void updateEntityCUBE(RenderableComponent* render, EntityGL4* entidad, Entity* entity, TYPE_OPERATION type);
	void updateEntityMESH(RenderableComponent* render, EntityGL4* entidad, Entity* entity, TYPE_OPERATION type);
	void updateEntityTEXT(RenderableComponent* render, EntityGL4* entidad, Entity* entity, TYPE_OPERATION type);
	void updateEntityGIZMOLIGTH(LightComponent* render, EntityGL4* entidad, Entity* entity, TYPE_OPERATION type);

	void processShader();
	void processLightShader(unsigned int id);
	void processViewProjectionShader(unsigned int id, const float* view, const float* projection, float* model);
	void iniciar();
	void destruir();
public:
	MotorGL();
	~MotorGL();
	void preRender();
	void renderFinal(unsigned int idShader=0, bool modeId=false);
	void render();
	void render(void *);
	void renderInterface();
	void refresh(int mode = 1); //modo 1= shader 2= update mesh
	void postRender(bool swap=true);
	bool inicializar(void * contexto, double ancho, double alto);
	char* nombre() { return (char*)"OPENGL 4"; };
		
	void ponerCamara(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);

	void updateEntity(void* entity, TYPE_OPERATION type);
	//void addEntity(void* entity);
	void removeEntity(void* entity);
	void clearEntity(EntityGL4* entidad);
	void removeEntities();
	void removeAll();
	/*void newEntity(TYPE_ENTITY type, renderable::Object* object);*/

	//TODO: Optimizar la carga de Shader para que no se dupliquen
	const byte* loadShader(const char* path);
	int loadShader(const char* path, Graphics::Shader::TYPE_SHADER type);
	void reloadShader(const char* path, Graphics::Shader::TYPE_SHADER type, int idShader, int idProgram);
	int compileShader(std::vector<short>* ids);
	int compileShader(int ps);
	int compileShader(std::vector<short>*, void* entity);
	int compileShader(int ps, void* entity);

	void changeCamera(Camera* camera);
	void resizeCamera();
	bool addTexture(float* image, unsigned int length, int width, int height, int& idTexture, modules::graphics::TextureImg::FORMAT_COLOR typeColor, int repeat = GL_REPEAT, int nearest = GL_NEAREST);
	static void closeWindow(GLFWwindow* window);
	//void renderNewViewPort(std::vector<Entity*> entidades, float x = -1.f, float y = 1.f, float width = 2.f, float height = 2.f);
	Entity* drawLine(float* vertex, unsigned countVertex, float r, float g, float b, float a, unsigned width = 1);
	Entity* drawLineLoop(float* vertex, unsigned countVertex, float r, float g, float b, float a, unsigned width = 1);
	Camera* getActiveCamera() {return camaraActual;};

	void generateTexture2D(unsigned int* id, const unsigned int width, const unsigned int height, TYPE_TEXTURE2D formatTexture);
	void generateTexture2DWithFBO(unsigned int* id, const unsigned int width, const unsigned int height, unsigned int depthFBO, TYPE_TEXTURE2D formaTexture, TYPE_FRAMEBUFER formatFB);
	void getFrameBuffer(unsigned int* id);
	void renderShadowMap(LightComponent* ligth, unsigned int &depthFBO, unsigned int &depthTexture2D, const unsigned int widthTexture2D, const unsigned int heightTexture2D, TYPE_SHADOW_MAP type);
	float getPixel_id(int x, int y);
	
};
#endif // !__MOTORGL_4
