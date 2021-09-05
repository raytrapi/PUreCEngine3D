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
	GLenum _mode;
	GLuint _vao=0; //Array de vertices -> Apunta a un buffer
	GLuint _vbo=0; //Buffer de vertices
	GLuint _ebo=0; //Indice de vertices -> Indica como se lee el buffer
	std::vector<GLuint> _texts; //Texturas
	std::vector<std::tuple<GLuint,int,int,void*, GLenum>> _fbos; //Buffer de frames
	int _numeroVertices;
	renderable::Object* _object;
	std::vector<GLuint> shadersPrograms;
public:
	EntityGL4() {
		_object = NULL;
	}
	EntityGL4(GLenum mode, renderable::Object* object) {
		_mode = mode;
		_object = object;
	};
	~EntityGL4() {
		clear();
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
	GLuint* getEBO() { return &_ebo; };
	std::vector<std::tuple<GLuint, int, int, void*, GLenum>>* getFBOs() { return &_fbos; };
	std::vector<GLuint>* getTexts() { return &_texts; };
	void addText(GLuint idTexture) {
		_texts.push_back(idTexture);
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

	void clear() {
		
		for (auto itr = _fbos.begin(); itr != _fbos.end(); itr++) {
			glDeleteFramebuffers(1, &(std::get<0>(*itr)));
		}
		_fbos.clear();
		for (auto itr = _texts.begin(); itr != _texts.end(); itr++) {
			glDeleteTextures(1, &(*itr));

		}
		_texts.clear();
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
				LOG_DBG("ERROR EN SHADER: Se ha producido un error en la coplilación de tipo \r\n\t%\r\n\t%", type, infoLog);
			}
		} else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				LOG_DBG("ERROR EN SHADER: Se ha producido un error al linkar el programa \r\n\t%\r\n\t%", type, infoLog);
			}
		}
	}
};

#endif // !_ENTITY_GL4
