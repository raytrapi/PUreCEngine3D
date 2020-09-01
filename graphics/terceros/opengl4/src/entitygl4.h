#ifndef _ENTITY_GL4
#define _ENTITY_GL4
#define GL_GLEXT_PROTOTYPES
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../../src/renderable/object.h"
#include <entity.h>
#include <vector>

struct EntityGL4 {
	GLenum _mode;
	GLuint _vao;
	GLuint _vbo;
	int _numeroVertices;
	renderable::Object* _object;
	std::vector<GLuint> shadersPrograms;
public:
	EntityGL4(GLenum mode, renderable::Object* object) {
		_mode = mode;
		_object = object;
	};
	~EntityGL4() {
		
	}
	GLenum getMode() { return _mode; };

	/**
		Obtiene el indice de nuestro array de vertices
		@return GLuint valor de tipo
	*/
	GLuint* getVAO() { return &_vao; };
	GLuint* getVBO() { return &_vbo; };


	int getVertextCount() {
		return _numeroVertices;
	}
	void setVertextCount(int number) {
		_numeroVertices = number;
	}

	renderable::Object* getObject() { return _object; };
	void addShaderProgram(GLuint idProgram) {
		shadersPrograms.push_back(idProgram);
	}
	const std::vector<GLuint>* getShadersPrograms() {
		
		return &shadersPrograms;
	}
};

#endif // !_ENTITY_GL4
