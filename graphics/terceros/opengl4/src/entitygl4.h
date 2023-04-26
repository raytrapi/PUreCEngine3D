#ifndef _ENTITY_GL4
#define _ENTITY_GL4
#define GL_GLEXT_PROTOTYPES
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


#include "../../src/renderable/object.h"
#include <entity.h>
#include <vector>
#include <tuple>
#include <string>

struct EntityGL4 {
	boolean inicializada=false;
	GLenum _mode;
	GLuint _vao=0; //Array de vertices -> Apunta a un buffer
	GLuint _vbo=0; //Buffer de vertices
	GLuint _vao_id = 0; //Array de vertices para Ids
	GLuint _vbo_id = 0; //Buffer de vertices para Ids
	GLuint _ebo=0; //Indice de vertices -> Indica como se lee el buffer
	std::vector<GLuint> _texts; //Texturas
	std::vector<std::tuple<GLuint,int,int,void*, GLenum>> _fbos; //Buffer de frames
	int _numeroVertices=0;
	renderable::Object* _object;
	std::vector<GLuint> shadersPrograms;
public:
	EntityGL4() {
		_object = NULL;
		//_numeroVertices = object->getVertexNumber();
	}
	EntityGL4(GLenum mode, int vertexNumber) {
		_mode = mode;
		_object = NULL;
		_numeroVertices = vertexNumber;
	};
	EntityGL4(GLenum mode, renderable::Object* object) {
		_mode = mode;
		_object = object;
		_numeroVertices = object->getVertexNumber();
	};
	~EntityGL4() {
		clear();
	}
	bool isInitiate() { 
		if (inicializada) {
			return true;
		} else {
			inicializada = true;
			return false;
		}
	}
	GLenum getMode() { return _mode; };

	/**
		Obtiene el indice de nuestro array de vertices
		@return GLuint valor de tipo
	*/
	GLuint* getVAO() { return &_vao; };
	/**
		Obtiene el indice de nuestro buffer de vertices
		@return GLuint valor de tipo
	*/
	GLuint* getVBO() { return &_vbo; };

	GLuint* getVAO_id() { return &_vao_id; };
	GLuint* getVBO_id() { return &_vbo_id; };
	GLuint* getEBO() { return &_ebo; };

	std::vector<std::tuple<GLuint, int, int, void*, GLenum>>* getFBOs() { return &_fbos; };
	std::vector<GLuint>* getTexts() { return &_texts; };
	unsigned addText(GLuint idTexture) {
		_texts.push_back(idTexture);
		return _texts.size() - 1;
	}
	GLuint* addFBO(int width=0, int height=0, void *data=NULL, GLenum scale=GL_LINEAR) {
		_fbos.push_back({ 0,width, height, data, scale });
		return &std::get<0>(_fbos[_fbos.size() - 1]);
	}
	int getVertextCount() {
		return _numeroVertices;
	}
	void setVertextCount(int number) {
		_numeroVertices = number;
	}

	renderable::Object* getObject() { return _object; };
	void setObject(renderable::Object* o) { _object=o; };
	void addShaderProgram(GLuint idProgram) {
		shadersPrograms.push_back(idProgram);
	}
	const std::vector<GLuint>* getShadersPrograms() {
		
		return &shadersPrograms;
	}
	void clearText() {
		for (auto itr = _texts.begin(); itr != _texts.end(); itr++) {
			glDeleteTextures(1, &(*itr));

		}
		_texts.clear();
	}
	void clear() {
		for (auto itr = _fbos.begin(); itr != _fbos.end(); itr++) {
			glDeleteFramebuffers(1, &(std::get<0>(*itr)));
		}/**/
		//_fbos.clear();
		clearText();
		if (_ebo != 0) {
			glDeleteBuffers(1, &_ebo);
			_ebo = 0;
		}
		glDeleteBuffers(1, &_vbo);
		_vbo = 0;
		glDeleteVertexArrays(1, &_vao);
		_vao = 0;
	}
	static void checkCompileErrors(GLuint shader, std::string type) {
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				DBG("ERROR EN SHADER: Se ha producido un error en la coplilación de tipo \r\n\t%\r\n\t%", type, infoLog);
			}
		} else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				DBG("ERROR EN SHADER: Se ha producido un error al linkar el programa \r\n\t%\r\n\t%", type, infoLog);
			}
		}
	}
};

struct LightGL4 {
	float position[3] = { 0,0,0 };              // Posición de la luz en el espacio //1 más para compesar la structura
	float ext1;
	float color[3] = { 0,0,0 };                 // Color de la luz
	float ext2;
	float constantAttenuation=0;  // Atenuación constante de la luz
	float linearAttenuation=0;    // Atenuación lineal de la luz
	float quadraticAttenuation=0; // Atenuación cuadrática de la luz
	// Para sombras:
	int castsShadows=0;           // Indica si la luz emite sombras
	float shadowMatrix[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };   // Matriz de proyección para sombras
	//sampler2D shadowMap;        // Textura de mapa de sombras

	void setPosition(float x, float y, float z) { position[0] = x; position[1] = y; position[2] = z; };
	void setColor(float r, float g, float b) { color[0] = r; color[1] = g; color[2] = b; };
};
const int NUM_LIGHTS=10;

#endif // !_ENTITY_GL4
