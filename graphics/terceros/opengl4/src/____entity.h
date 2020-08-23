#ifndef _ENTITY_GL4
#define _ENTITY_GL4
#include "../src/renderable/object.h"
#include <vector>
struct Entity {
	GLenum _mode;
	GLuint _vao;
	int _numeroVertices;
	renderable::Object* _object;
	std::vector<GLuint> shadersPrograms;
public:
	Entity(GLenum mode, renderable::Object* object) {
		_mode = mode;
		_object = object;
	};
	GLenum getMode() { return _mode; };
	
	/**
		Obtiene el indice de nuestro array de vertices
		@return GLuint valor de tipo
	*/
	GLuint *getVAO() { return &_vao; };

	int getVertextCount() {
		return _numeroVertices;
	}
	void setVertextCount(int number) {
		_numeroVertices=number;
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
