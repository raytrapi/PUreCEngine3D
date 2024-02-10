#include "object.h"
#include "../renderableComponent.h"
#include "../../../src/entity.h"
#include "../../../utilidades/project/genericFile.h"
//#include "../../../../graphics/terceros/opengl4/src/imgui/"
#include "../../../utilidades/files/filesControl.h"
//#include "../../../../graphics/terceros/opengl4/src/imgui/interface.h"
#include "cube.h"
renderable::Object::~Object() {
	//utiles::Log::debug("borro obj");
	borrar();
	borrarIdsMaterial();
}
void renderable::Object::setName(std::string name) {
	nombre = name;
}
void renderable::Object::borrar() {
	borrarMesh();
	borrarMaterial();
	cambio = true;
	
}
void renderable::Object::borrarVertex() {
	numeroVertices = 0;
	if (vertices != NULL) {
		delete[] vertices;
		vertices = NULL;
	}
}
void renderable::Object::borrarMesh() {
	borrarVertex();
	if (normales) {
		delete[] normales;
		normales = NULL;
	}
	if (colores) {
		delete[] colores;
		colores = NULL;
	}
	if (indices) {
		delete[] indices;
		indices = NULL;
	}
	if (uvs) {
		delete[] uvs;
		uvs = NULL;
	}

	if (caras) {
		//Borramos la lista dentro de las caras
		for (auto cara : *caras) {
			for (auto vs : cara) {
				delete[] vs;
			}
			cara.clear();
		}
		caras->clear();
		delete caras;
		caras = NULL;
	}

	if (modosColor) {
		delete[] modosColor;
		modosColor = NULL;
	}
}
void renderable::Object::borrarMaterial() {
	for (auto itr = materials.begin(); itr != materials.end(); itr++) {
		if (std::get<1>(*itr)) {
			if (std::get<0>(*itr) != NULL) {
				std::get<0>(*itr)->removeChange();
				delete std::get<0>(*itr);
			}
		}
	}
	materials.clear();
}
void renderable::Object::borrarIdsMaterial() {
	if (idsMateriales) {
		delete[]idsMateriales;
		idsMateriales = NULL;
	}
}
void renderable::Object::ponerMesh(float* mesh, float* normals, float * colors, int * indexs) {
	borrar();
	int longitud = sizeof(mesh);
	vertices = new float[longitud];
	for (int i = 0; i < longitud; i++) {
		vertices[i] = mesh[i];
	}
	numeroVertices = longitud / 3;
	//TODO: Controlar que el número de normales y los colores sea igual a los vertices
	if (normals) {
		int longitud = sizeof(normals);
		normales = new float[longitud];
		for (int i = 0; i < longitud; i++) {
			normales[i] = normals[i];
		}
	}
	if (colors) {
		int longitud = sizeof(colors);
		colores = new float[longitud];
		for (int i = 0; i < longitud; i++) {
			colores[i] = colors[i];
		}
	}
	if (indexs) {
		int longitud = sizeof(indexs);
		indices = new int[longitud];
		for (int i = 0; i < longitud; i++) {
			indices[i] = indexs[i];
		}
	}
}

void renderable::Object::materialUpdated(Texture* texture, Material* material) {
	materialUpdated_I(texture, material);
	cambio = true;
	setToRender(true);
	
};

/**
* Add material but not delete when remove the mesh
* */
unsigned renderable::Object::setMaterial(Material* m, int pos, bool del) {

	if (pos > -1 && pos<materials.size()) {
		delete std::get<0>(materials[pos]);
		if (del) {
			std::get<0>(materials[pos]) = new Material(*m);
		} else {
			std::get<0>(materials[pos]) = m;
		}
		modoColor = TEXTURE;
		std::get<1>(materials[pos]) = del;
		std::get<0>(materials[pos])->onChange([&](Texture* t, Material* m) {this->materialUpdated(t, m); });
		return pos;
	} else {
		if (m) {
			modoColor = TEXTURE;
			materials.push_back({ m, del });
			m->onChange([&](Texture* t, Material* m) {this->materialUpdated(t,m); });
			return materials.size() - 1;
		} else {
			return 0;
		}
	}

}
/**
* Add material and delete when remove the mesh
* */
unsigned renderable::Object::setMaterial(Material m, int pos, bool del) {
	Material* m2 = new Material(m);
	return setMaterial(m2, pos, del);
	
}

Material* renderable::Object::getMaterial(unsigned int ix) {
	return std::get<0>(materials[ix]);
}

RenderableComponent* renderable::Object::getRenderable() {
	return renderizador;
}

std::vector<Material*> renderable::Object::getMaterials() {
	std::vector<Material*> materiales;
	for (int i = 0; i < materials.size(); i++) {
		materiales.push_back(std::get<0>(materials[i]));
	}
	return materiales;
}

float* renderable::Object::getUVs() {
	return uvs;
}

unsigned int renderable::Object::getIdTexture() {
	if (materials.size() > 0) {
		return std::get<0>(materials[0])->getIdTexture();
	}
	return 0;
}

int renderable::Object::getNormalsNumber() {
	return numeroNormales;
}

int renderable::Object::getVertexNumber() {
	return numeroVertices;
}

int renderable::Object::getFacesNumber() {
	return caras->size();
}
void renderable::Object::setUV(float** uv) {
	/*if (uvs) {
		delete[] uvs;
		uvs = NULL;
	}*/
	if (this->uvs != NULL) {
		for (int i = 0; i < numeroVertices; i++) {
			for (int jC = 0; jC < 2; jC++) {
				this->uvs[(i * 2) + jC] = uv[i][jC];
			}
		}
	}
	
	cambio = true;
	actualizarVertices = true;
	setToRender(true);
}
void renderable::Object::setUV(int pos, float u, float v) {
	int posF = pos * 2;
	this->uvs[posF] = u;
	this->uvs[posF+1] = v;
}
void renderable::Object::setToRender(bool toRender) {
	RenderableComponent* renderizador = getRenderable();
	if (renderizador!=NULL) {
		renderizador->setUpdated(toRender);
	}
} 
/*int renderable::Object::desserializar(std::string s, int pos, Component* c) {
	while (pos < s.length()) {
		auto [posT, clave, valor] = GenericFile::unserializate(s, pos + 1);
		pos = posT;
		if (clave == "tipo") {
			renderable::Object::TYPE t = (renderable::Object::TYPE)std::atoi(valor.c_str());
			switch (t){
				
				default:
					ERR("No se reconoce el tipo de Objeto [Tipo: %]", (int)t);
					return s.length();
					break;
			}
		}
	}
	return pos;
}/**/
int renderable::Object::desserializar(std::string s, int pos, RenderableComponent* c) {
	while (pos < s.length()) {
		auto [posT, clave, valor] = GenericFile::unserializate(s, pos + 1);
		pos = posT;
		if (clave == "tipo") {
			renderable::Object::TYPE t = (renderable::Object::TYPE)std::atoi(valor.c_str());
			switch (t) {
			case renderable::Object::TYPE::CUBE:
			{
				auto cubo = c->add<Cube>();
				cubo->desserializar(valor);
				pos += valor.length() + 2;
			}
			break;
			default:
				ERR("No se reconoce el tipo de Objeto [Tipo: %]", (int)t);
				return s.length();
				break;
			}
		}
	}
	return pos;
}



int renderable::Object::saveState(std::vector<unsigned char>* data, bool withID) { 
	if (withID) { 
		Serializer::serialize(data, this); 
	}; 
	saveState_interno(data, withID);
	Serializer::serialize(data, (int)materials.size());
	for (auto m : materials) {
		Serializer::serialize(data, (unsigned long long)std::get<0>(m)->getUID());
		std::get<0>(m)->saveState(data, withID);
	}
	return data->size(); 
};
void renderable::Object::restoreState(std::vector<unsigned char>* data, bool withID) { 
	Object* o=NULL ;
	if (withID) {
		DBG("Restaurando");
	};
	restoreState_interno(data, withID); 
	int numMateriales = 0;
	Deserializer::deserialize(&numMateriales);
	for (int i = 0; i < numMateriales; i++) { 
		unsigned long long uidMat = 0; 
		Deserializer::deserialize(&uidMat);
		Material *m2 = NULL;
		if (withID) {
			Deserializer::deserialize(&m2);
		}
		auto m = new Material(uidMat);
		m->restoreState(data, withID);
		auto ts = m->getTextures();
		for (auto t : *ts) {
			materialUpdated(t, NULL);
		}
		if (m) {
			setMaterial(m);
			materialUpdated(NULL, m);
		}
		//auto mat = new Material(uidMat);
		//materials.push_back({ mat,true });
	}
	if (numMateriales == 0) {
		modoColor = COLOR;
	} else {
		modoColor = (std::get<0>(materials[0])->getTextures()->size() > 0) ? TEXTURE : COLOR;
	}
	
	cambio = true;
	setToRender(true);
};

bool renderable::Object::interfazImGUI(ImGuiContext* imgui) {
	interfazImGUI_C(imgui);
	int ixM = 0;
	auto global = Global::getInstance();// renderizador->getGraphic()->getGlobal();
	float u1 = 0;
	float u2 = 0;
	float v1 = 0;
	float v2 = 0;
	for (auto m : materials) {
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		//TODO: Esto se puede mejorar por ejemplo teniendo un char * con dos huecos para el número de textura. Solo dejariamos 99
		std::string texto = std::string("Elemento ") + std::to_string(ixM);
		ImGui::Text(texto.c_str());
		ImGui::TableNextColumn();
		auto mat = std::get<0>(m);
		
		if (mat) {
			auto n = mat->getName();
			ImGui::AlignTextToFramePadding();
			u1 = global->uBotonCompilacion * 6;// InterfaceGL::uBotonCompilacion * 0;
			u2 = global->uBotonCompilacion * 8;
			v1 = 1.0f - (2 * global->vBotonCompilacion);
			v2 = 1.0f - (4 * global->vBotonCompilacion);
			if (n) {
				u1 = global->uBotonCompilacion * 4;// InterfaceGL::uBotonCompilacion * 0;
				u2 = global->uBotonCompilacion * 6;
			}
			//TODO: Habría que sustituirlo por la imagen de la renderización de la textura
			ImGui::Image((void*)(intptr_t)global->idTexturaIconos, ImVec2(64, 64), ImVec2(u1, v1), ImVec2(u2, v2));
			
		} else {
			
			
			
			//if (renderizador) {
				u1 = global->uBotonCompilacion * 6;// InterfaceGL::uBotonCompilacion * 0;
				u2 = global->uBotonCompilacion * 8;
				v1 = 1.0f - (2 * global->vBotonCompilacion);
				v2 = 1.0f - (4 * global->vBotonCompilacion);
				ImGui::Image((void*)(intptr_t)global->idTexturaIconos, ImVec2(64, 64), ImVec2(u1, v1), ImVec2(u2, v2));
			//} else {
			//	ImGui::Text("Vacio");
			//}


			
		}
		//Drop del material
		if (!ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::BeginDragDropTarget()) {
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DRAG_MATERIAL")) {
				if (payload->DataSize == sizeof(DragFile)) {
					auto datos = *(DragFile*)payload->Data; 
					setMaterial(new Material(datos.UID), ixM);
					std::get<0>(materials[ixM])->setName(datos.name.c_str());

					//DBG("Soltamas el fichero % sobre el objeto %", datos.name, objetoEncima->getName().c_str());
				}
			}

			ImGui::EndDragDropTarget();
		}
		ImGui::SameLine();
		u1 = global->uBotonCompilacion * 7;// InterfaceGL::uBotonCompilacion * 0;
		u2 = global->uBotonCompilacion * 8;
		v1 = 1.0f - (1 * global->vBotonCompilacion);
		v2 = 1.0f - (2 * global->vBotonCompilacion);


		ImGui::PushID(100 + ixM);
		if (ImGui::ImageButton((void*)(intptr_t)global->idTexturaIconos, ImVec2(32, 32), ImVec2(u1, v1), ImVec2(u2, v2))) {
			materials.erase(materials.begin() + ixM);
			ImGui::PopID();
			break;
		};
		ImGui::PopID();
		
		if (mat) {
			//ImGui::EndTable();
			mat->interfazImGUI(imgui);
			//char* nombreTabla = NULL;
			//CONCAT_CHAR("##",CONCAT_CHAR("dd","kk",nombreTabla), nombreTabla)
			//ImGui::BeginTable("##o2", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_NoSavedSettings);
		}

		ixM++;
	}
	ImGui::EndTable();
	if (ImGui::Button(U8(Nuevo material))) {
		setMaterial(new Material());
	};
	ImGui::BeginTable("##o",2);
	return true;
}
std::vector<renderable::Object*> renderable::Object::objetos;