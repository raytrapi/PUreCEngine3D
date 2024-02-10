#include "mesh.h"
//#include <algorithm>
#include "../../../components/modulos/renderables/renderableComponent.h"
renderable::Mesh::Mesh(){
}
renderable::Mesh::~Mesh() {
	borrarCaras();
}

void renderable::Mesh::borrarCaras() {
	if (caras != NULL) {
		for (auto cara : *caras) {
			for (auto vec : cara) {
				delete[]vec;
			}
		}
		delete caras;
	}
	caras = NULL;
}
void renderable::Mesh::setMesh(float* mesh, float* normals, float *colors) {
	ponerMesh(mesh, normals,colors);
}

void renderable::Mesh::setSize(float length) {}

float renderable::Mesh::getSize() {
	return 0.0f;
}

/**
* Get the number of all components to the mesh
* Obtenemos el tamaño total de los componentes de la malla
**/
/*int renderable::Mesh::getAllSize() {
	return numCoordenadas;
}

float* renderable::Mesh::getMesh() {
	return vertices;
}
float* renderable::Mesh::getNormals() {
	return normales;
}
float* renderable::Mesh::getColors() {
	return colores;
}*/
int* renderable::Mesh::getIndexs() {
	return indices;
}





void renderable::Mesh::setFaces(std::vector<std::vector<int>*>* faces, std::vector<float**>* vectors, std::vector<float**>* color, std::vector<float**>* normals, std::vector<float**>* uvs, renderable::Object::MODE_COLOR mode) {
	setTriangles(vectors, color, normals, uvs, mode);
	caras = new std::vector<std::vector<const float*>>;
	for (int i = 0; i < faces->size(); i++) {
		
		std::vector<const float*> ultimo = std::vector<const float*>();
		for (int j = 0; j < faces->operator[](i)->size(); j++) {
			ultimo.push_back(new float[]{ vertices[j * 3],vertices[(j * 3) + 1],vertices[(j * 3) + 2] });
		}
		caras->push_back(ultimo);
	}

}

void renderable::Mesh::setTriangles(std::vector<float **>*triangulos,std::vector<float**>* colors, std::vector<float**>* normals, std::vector<float**>* uvs, renderable::Object::MODE_COLOR mode) {
	borrarMesh();
	borrarIdsMaterial();
	float cara[4] = { 0,0,0,0 };
	float zMin = 0;
	modoColor = mode;
	numeroVertices = triangulos->size()*3;
	numCoordenadas = numeroVertices * 13; //3+3+4+2+1 (3 coordenadas + 3 normales + 4 color + 2 uv + 1 idTextura )
	int numComponentes = numeroVertices * 3;
	vertices = new float[numComponentes];
	normales= new float[numComponentes];
	colores = new float[numeroVertices * 4];
	
	idsMateriales = new float[numeroVertices];
	this->uvs = new float[numeroVertices * 2]; //Solo hay dos componentes por uv
	int iMalla = 0;
	int iNormales = 0;
	int iColores = 0;
	int iUVs = 0;
	int iIdMaterial = 0;
	
	for (int i = 0; i < triangulos->size(); i++) {
		//No comprobamos que efectivamente existan al menos 3 coordenadas para acelerar el proceso de carga.
		float** vertice = triangulos->operator[](i);
		if (i == 0) {
			zMin = vertice[0][2];
			cara[1] = cara[3] = vertice[0][0];
			cara[0] = cara[2] = vertice[0][1];

		}
		for (int iV = 0; iV < 3; iV++) {
			for (int iC = 0; iC < 3; iC++) {
				vertices[iMalla++] = vertice[iV][iC];
				if (iC == 0) {
					if (vertice[iV][iC] > cara[1]) {
						cara[1] = vertice[iV][iC];
					}else if (vertice[iV][iC] < cara[3]) {
						cara[3] = vertice[iV][iC];
					}
				}else if (iC == 1) {
					if (vertice[iV][iC] > cara[0]) {
						cara[0] = vertice[iV][iC];
					} else if (vertice[iV][iC] < cara[2]) {
						cara[2] = vertice[iV][iC];
					}
				} else {
					if (zMin > vertice[iV][iC]) {
						zMin = vertice[iV][iC];
					}
				}
			}
		}
		float normal[3] = { 0.f,0.f,1.f };
		if (normals) {
			for (int iN = 0; iN < 3; iN++) {
				for (int jN = 0; jN < 3; jN++) {
					normales[iNormales++] = normals->operator[](i)[iN][jN];
				}
			}
		} else {
									
			float ux = vertice[1][0] - vertice[0][0];
			float uy = vertice[1][1] - vertice[0][1];
			float uz = vertice[1][2] - vertice[0][2];

			// Calcular el vector V
			float vx = vertice[2][0] - vertice[0][0];
			float vy = vertice[2][1] - vertice[0][1];
			float vz = vertice[2][2] - vertice[0][2];

			// Calcular el producto cruz de U y V para obtener la normal
			
			normal[0] = vy * uz - vz * uy;
			normal[1] = vz * ux - vx * uz;
			normal[2] = vx * uy - vy * ux;/**/

			// Normalizar la normal
			float magnitud = std::sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
			normal[0] /= magnitud;
			normal[1] /= magnitud;
			normal[2] /= magnitud;
			normales[iNormales++] = normal[0];
			normales[iNormales++] = normal[1];
			normales[iNormales++] = normal[2];
			normales[iNormales++] = normal[0];
			normales[iNormales++] = normal[1];
			normales[iNormales++] = normal[2];
			normales[iNormales++] = normal[0];
			normales[iNormales++] = normal[1];
			normales[iNormales++] = normal[2];
		}
		/**/
		/* Calculo obtenido de https://www.khronos.org/opengl/wiki/Calculating_a_Surface_Normal */

		//Se repite 3 veces porque cada vertice del mismo triangulo tiene la misma normal
		
		
		//LOG_DBG("Longitud del array %", sizeof(colors));
		if (colors && colors->size() > i) {
			for (int iC = 0; iC < 3; iC++) {
				for (int jC = 0; jC < 4; jC++) {
					colores[iColores++] = colors->operator[](i)[iC][jC];
				}
				
			}
		} else {
			for (int iC = 0; iC < 3; iC++) {
				for (int jC = 0; jC < 4; jC++) {
					colores[iColores++] = 1.0f;
				}
			}
		}
		if (uvs == NULL || uvs->size()<=i) {
			for (int iC = 0; iC < 3; iC++) {
				for (int jC = 0; jC < 2; jC++) {
					this->uvs[iUVs + jC] = 1.0f;
				}
				iUVs += 2;
			}
		} else {
			for (int iC = 0; iC < 3; iC++) {
				for (int jC = 0; jC < 2; jC++) {
					this->uvs[iUVs + jC] = uvs->operator[](i)[iC][jC];//uvs[i * 3 + iC][jC];
				}
				iUVs += 2;
			}
		}

		//Cargamos los materiales
		idsMateriales[iIdMaterial++] = 0; //TODO: Esto se obtendrá de los materiales que tendremos que pasar como un parámetro

		
	}

	//AHORA Cargamos los materiales
	numeroModosColor = 1;
	modosColor = new MODE_COLOR[numeroModosColor];
	modosColor[0] = mode;

	cambio = true;

	RenderableComponent* renderizador = getRenderable();
	if (renderizador) {
		renderizador->setUpdated(true);
	}/**/

	//Creamos la única cara que tendremos
	borrarCaras();
	
	caras = new std::vector<std::vector<const float*>>();
	std::vector<const float*> caraV = std::vector<const float*>();
	caraV.push_back(new float[] { cara[3], cara[0], zMin });
	caraV.push_back(new float[] { cara[1], cara[0], zMin });
	caraV.push_back(new float[] { cara[1], cara[2], zMin });
	caraV.push_back(new float[] { cara[3], cara[2], zMin });
	caras->push_back(caraV);
}

void renderable::Mesh::setTriangles(int triangles, float* vertex, float* colors, float* normals, float* uvs, renderable::Object::MODE_COLOR mode){
	modoColor = mode;
	numeroVertices = triangles * 3;
	numCoordenadas = numeroVertices * 13; //3+3+4+2+1 (3 coordenadas + 3 normales + 4 color + 2 uv + 1 idTextura )
	if (vertices) {
		delete[] vertices;
	}
	vertices = vertex;
	if (colores) {
		delete[] colores;
	}
	if (colors) {
		colores = colors;
	} else {
		int numVertices = triangles * 3;
		colores = new float[ numVertices * 4];
		int posI = 0;
		for (int i = 0; i < numVertices; i++) {
			colores[posI++] = 1.0f; colores[posI++] = 1.0f; colores[posI++] = 1.0f; colores[posI++] = 1.0f;
		}
	}/**/
	if (normales) {
		delete[] normales;
	}
	if (normals) {
		normales = normals;
	} else {
		int numVertices = triangles * 3;
		normales = new float[numVertices * 3];
		int posI = 0;
		for (int i = 0; i < numVertices; i++) {
			normales[posI++] = 0.0f; normales[posI++] = 1.0f; normales[posI++] = 0.0f;
		}
	}

	if (this->uvs) {
		delete[] this->uvs;
	}
	if (modosColor) {
		delete[]modosColor;
		modosColor = 0;
	}
	if (mode == TEXTURE) {
		numeroModosColor = 1;
		modosColor = new MODE_COLOR[numeroModosColor];
		modosColor[0] = mode;
	}
	this->uvs = uvs;


	cambio = true;

	RenderableComponent* renderizador = getRenderable();
	if (renderizador) {
		renderizador->setUpdated(true);
	}/**/
}

void renderable::Mesh::setObject(std::vector<float*>* vertex, std::vector<int>* indexes, std::vector<float**>* normals, float** color) {
	borrar();
	numeroVertices = vertex->size();
	numCoordenadas = numeroVertices * 3;
	int numComponentes = numeroVertices * 3;
	vertices = new float[numCoordenadas];
	indices = new int[indexes->size()];
	normales = new float[numComponentes];
	colores = new float[numComponentes];
	int iVertice = 0;
	int iNormales = 0;
	int iColores = 0;
	for (int i = 0; i < numeroVertices; i++) {
		for (int j = 0; j < 3; j++) {
			vertices[iVertice++] = vertex->operator[](i)[j];
		}
	}
	for (int i = 0; i < numComponentes; i++) {
		indices[i] = indexes->operator[](i);
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				normales[iNormales++] = normals->operator[](i)[j][k];
			}
		}
	}
}

void renderable::Mesh::loadOBJ(const char* file) {
	//El fiel será o bien un obj o bien un pc3d
	auto l = strlen(file);
	char c=file[l - 3];
	char* fichero = NULL;
	bool original = true;
	if (c == 'c') {
		//es un pc3
		char* fT = GenericFile::getString(file, 0);

		auto p = (Global::getInstance()->getPathRoot() + "/" + fT);
		auto l = p.length();
		fichero = new char[l + 1];
		for (int i = 0; i < l; i++) {
			fichero[i] = p[i];
		}
		fichero[l] = '\0';
		
		//fichero = GenericFile::getString(file, 0);
		original = false;
	}
	//TODO: Solo funcionará con el primer objeto de maya del fichero
	auto infos = imports::Model::load(original?file:fichero);
	if (infos.size()>0) {
		//Tenemos el objeto
		auto m = infos[0];
		setTriangles((m->triangles), (m->colors), (m->normals), (m->uvs), (renderable::Object::MODE_COLOR)(m->mode));
	}else {
		ERR("No se encuntra el objeto % en el fichero [%]", 0, file);
	}
	for (auto info : infos) {
		delete info;
	}
	if (!original) {
		delete[]fichero;
	}
}







void renderable::Mesh::materialUpdated_I(Texture* texture, Material* material) {
	if (material) {
		auto col = material->getAmbient();
		if (col && colores) {
			int k = 0;
			for (int i = 0; i < numeroVertices; i++) {
				colores[k++] = col[0];
				colores[k++] = col[1];
				colores[k++] = col[2];
				colores[k++] = col[3];
			}
		}
		modoColor = material->getTextures()->size() == 0 ? COLOR : TEXTURE;
		if (modosColor && numeroModosColor>0) {
			modosColor[0] = material->getTextures()->size() == 0 ? COLOR : TEXTURE;
		}
	}
}



bool renderable::Mesh::interfazImGUI_C(ImGuiContext* imgui) {

	return true;
};
int renderable::Mesh::saveState_interno(std::vector<unsigned char>* data, bool withID) {
	int l = 0;
	l+= Serializer::serialize(data, (int)Object::TYPE::MESH);
	l+=Serializer::serialize(data, uidObject);
	return l;
};
void renderable::Mesh::restoreState_interno(std::vector<unsigned char>* data, bool withID) {
	if (data != 0) {
		Deserializer::stackBytes(data);
	}
	Deserializer::deserialize(&uidObject);
	//Procesamos el uid si existe
	if (uidObject != 0) {
		auto rutaFichero = FileControl::getFileUID(uidObject);
		if (rutaFichero != 0) {
			auto tipoFichero = GenericFile::getType(rutaFichero);
			if (tipoFichero.has_value()) {
				switch (*tipoFichero) {
					case TYPE_FILE::FILE_OBJ:
						loadOBJ(rutaFichero);
					default:
						ERR("No se reconoce el fichero con UID % [%]", uidObject, rutaFichero);
						break;
				}
			}else {
				ERR("No se reconoce el fichero con UID % [%]", uidObject, rutaFichero);
			}
		}else {
			ERR("No se ha podido encontrar el UID %", uidObject);
		}
	}



	if (data != 0) {
		Deserializer::unstackBytes();
	}
};
