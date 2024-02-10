#include "material.h"

#include "../../../utilidades/global/global.h"
#include "../../../utilidades/project/UIDProject.h"
#include <log/log.h>
#include <files/filesControl.h>

Material::Material() {
	lenA = 4;
	ambient = new float[lenA];
	nombre = new char[6] {'v', 'a', 'c', 'i', 'o', '\0'};

}
Material::Material(UID uid) {
	//De momento será una carpeta
	//COPY_CHAR(UID, fichero);
	this->uid = uid;
	auto ruta = FileControl::getFileUID(uid);
	if (ruta == NULL) {
		return;
	}
	if (ruta) {
		COPY_CHAR(ruta, fichero);
	}
	setName(ruta);
	lenA = 4;
	ambient = new float[lenA] {1.0f, 1.0f, 1.0f, 1.0f};
	//textures.push_back(new Texture("H:\\Desarrollo\\motor_videjuegos_sandbox\\tetris\\content\\Materiales\\tablero.png"));
}
Material::Material(const Material& m) {

	ambient = new float[m.lenA];
	for (int i = 0; i < m.lenA; i++) {
		ambient[i] = m.ambient[i];
	}
	lenA = m.lenA;
	typeAmbient = m.typeAmbient;
	lenD = m.lenD;
	difuse = new float[lenD];
	for (int i = 0; i < lenD; i++) {
		difuse[i] = m.difuse[i];
	}
	typeDifuse = m.typeDifuse;

	lenS = m.lenS;
	specular = new float[lenS];
	for (int i = 0; i < lenS; i++) {
		specular[i] = m.specular[i];
	}
	typeSpecular = m.typeSpecular;
	lenE = m.lenE;
	emission = new float[lenE];
	for (int i = 0; i < lenE; i++) {
		emission[i] = m.emission[i];
	}
	typeEmission = m.typeEmission;
	ilumination = m.ilumination;
	opacity = m.opacity;
	exponenteSpecular = m.exponenteSpecular;
	sharpness = m.sharpness;
	densityOptical = m.densityOptical;

	for (int i = 0; i < m.imgTextures.size(); i++) {
		imgTextures.push_back(new TextureImg(*m.imgTextures[i]));
	}
	for (int i = 0; i < m.textures.size(); i++) {
		textures.push_back(new Texture(*m.textures[i]));
	}

}
Material::~Material() {
	//DBG_F("Destruyo el material");
	for (int i = 0; i < textures.size(); i++) {
		if (textures[i] != NULL) {

			//TODO: TENEMOS QUE LIBERAR LA TEXTURA DE LA MEMORIA DE LA TARJETA GRÁFICA
			delete textures[i];
		}
	}
	textures.clear();
	for (int i = 0; i < imgTextures.size(); i++) {
		delete imgTextures[i];
	}
	imgTextures.clear();
	if (ambient != NULL) {
		delete[]ambient;
		ambient = NULL;
	}
	if (difuse != NULL) {
		delete[]difuse;
		difuse = NULL;
	}
	DELETE_MULTI(specular);
	DELETE_MULTI(emission);
	DELETE_MULTI(nombre);
	DELETE_MULTI(fichero);
	
}
void Material::setName(const char* name) {
	DELETE_MULTI(nombre);
	
	int l = strlen(name);
	nombre = new char[l + 1];
	for (int i = 0; i < l; i++) {
		nombre[i] = name[i];
	}
	nombre[l] = '\0';
}

void Material::setTexture(Texture* t) {
	this->textures.push_back(t);
}
void Material::setTexture(unsigned int idTexture) {
	Texture* t = new Texture();
	t->setTexture(idTexture);
	this->textures.push_back(t);
};
void Material::setTexture(float* img, unsigned int length, int width, int height, TextureImg::FORMAT_COLOR formatColor, int repeat, int nearest) {
	Texture* t = new Texture();
	t->setTexture(img, length, width, height, formatColor, repeat, nearest);
	this->textures.push_back(t);

};

void Material::setCode(const char* code) {
	codigo = "";
	auto l = strlen(code);
	for (int i = 0; i < l; i++) {
		codigo += code[i];
	}
	

}



std::expected<bool, int> Material::createFileMaterial(const char* path) {
	std::filesystem::path ruta(Global::getPathRoot() + path);
	if (ruta.extension() != ".pc3d") {
		ruta += ".pc3d";
	}
	if (std::filesystem::exists(ruta)) {
		//return std::unexpected(Error(-1, "El fichero ya existe"));
		return std::unexpected(-1);
	}

	Material m;
	if (m.fichero != NULL) {
		delete [] m.fichero;
	}
	auto l = ruta.string().length();
	m.fichero = new char[l+1];
	for (int i = 0; i < l; i++) {
		m.fichero[i] = ruta.string()[i];
	}
	m.fichero[l] = '\0';
	
	m.save();

	return true;

}

void Material::save() {
	std::ofstream fs(fichero, std::ios::binary);
	unsigned int longitud = strlen(UID_MATERIAL) + 1;
	fs.write((char*)&longitud, sizeof(unsigned int));
	fs.write(UID_MATERIAL, longitud);
	if (uid == 0) {
		uid= FileControl::generateUID<unsigned long long>();
	}
	fs.write((char*)&uid, sizeof(unsigned long long));

	longitud = 0; //Longitud imagen
	float* imagen = 0;
	if (idImagenIcono != -1) {
		//TODO: Obtener información imagen
	}
	fs.write((char*)&longitud, sizeof(unsigned int));
	if (longitud > 0) {
		//TODO: Guardar información de la imagen
	}

	//Shader de fragmento


	//Parámetros del material

	//Parte de código del material
	longitud = codigo.length();
	fs.write((char*)&longitud, sizeof(unsigned int));
	fs.write(codigo.c_str(), longitud);

	fs.close();
}
void Material::load(const char* path) {
	COPY_CHAR(path, fichero);
	auto uid = GenericFile::getUID_P(path);
	if (uid.has_value()) {
		this->uid = (*uid).first;
		//TODO: cargar el resto de informacion
		std::ifstream fs(path, std::ios::binary);
		fs.seekg((*uid).second);
		fs.close();
	}else {
		ERROR((char*)u8"No se ha podido coger la información");
	}

}
Material* Material::load(long long UID) {
	auto path = FileControl::getFileUID(UID);
	//std::filesystem::path ruta(Global::getPathRoot() + path); //TODO: Ahora se está almacenando la ruta absoluta, ¿Sería mejor la relativa? Seguramente si
	std::filesystem::path ruta( path);
	if (std::filesystem::exists(ruta)) {/**/
		DBG("Se ha encontrado el fichero");
		auto m = new Material();
		m->load(path);
		return m;
	}
	ERROR("El fichero no existe [%]", ruta.c_str());
	return NULL;
}
unsigned long long Material::getUID(const char* path) { 

	if (!std::filesystem::exists(path)) {
		ERROR("El fichero no existe [%]", path);
	}else {
		unsigned long long uid;
		std::ifstream fs(path, std::ios::binary);
		fs.seekg(sizeof(unsigned int) + strlen(UID_MATERIAL) + 1);
		fs.read((char*)&uid, sizeof(unsigned long long));
		unsigned int pos = fs.tellg();
		return uid;
	}
	return 0; 
}

bool Material::interfazImGUI(ImGuiContext* imgui) {
	//ImGui::Text(std::to_string(uid).c_str());
	bool cambio = false;
	bool abierto = false;
	if (this->nombre) {
		abierto=ImGui::CollapsingHeader(this->nombre);
	}else {
		abierto = ImGui::CollapsingHeader("SIN_NOMBRE");
	}
	if (abierto) {
		ImGui::BeginTable("##M3", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable );
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text("Albedo");
		ImGui::TableNextColumn();
		if (textures.size() > 0) {
			int iTextura = 0;
			for (auto textura : textures) {

				
				//ImGui::Text(textura->getPath());
				//ImGui::
				ImGui::Image(ImTextureID(textura->getIdTexture()), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
				if (!ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::BeginDragDropTarget()) {
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DRAG_IMAGEN")) {
						if (payload->DataSize == sizeof(DragFile)) {
							auto datos = *(DragFile*)payload->Data;
							textura->setIdTexture(datos.idImagen);
							textura->setPath((datos.path+"/"+datos.name).c_str());
							cambio = cambio || true;

							//DBG("Soltamas el fichero % sobre el objeto %", datos.name, objetoEncima->getName().c_str());
						}
					}

					ImGui::EndDragDropTarget();
				}
				if(ImGui::Button("Borrar")) {
					delete textura;
					textures.erase(textures.begin() + iTextura);
					if (funcionCambio) {
						funcionCambio(NULL, this);
					}
					break;
				} else {
					//TODO: Mejorar esta
					auto [u1, v1, u2, v2] = textura->getUV();
					bool cambiaUV = false;
					float uv1[2]{ u1,v1 };
					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text("U1, V1");
					ImGui::TableNextColumn();
					cambiaUV = cambiaUV || ImGui::DragFloat2("##u1_v1", uv1, 0.05F);
					float uv2[2]{ u2,v2 };
					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text("U2, V2");
					ImGui::TableNextColumn();
					cambiaUV = cambiaUV || ImGui::DragFloat2("##u2_v2", uv2, 0.05F);
					if (cambiaUV) {
						textura->setUV(uv1[0], uv1[1], uv2[0], uv2[1]);
						//cambio = cambio || true;
						if (funcionCambio) {
							funcionCambio(textura, NULL);
						}
					}
				}
				iTextura++;
			}
		} else {
			if (ImGui::ColorPicker4("##albedo", ambient)) {
				cambio = cambio || true;
			};
			if (!ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::BeginDragDropTarget()) {
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DRAG_IMAGEN")) {
					if (payload->DataSize == sizeof(DragFile)) {
						auto datos = *(DragFile*)payload->Data;
						auto textura = new Texture();

						textura->setIdTexture(datos.idImagen);
						textura->setPath((datos.path + "/" + datos.name).c_str());
						textures.push_back(textura);
						cambio = cambio || true;
						//DBG("Soltamas el fichero % sobre el objeto %", datos.name, objetoEncima->getName().c_str());
					}
				}

				ImGui::EndDragDropTarget();
			}
		}
		ImGui::EndTable();

	}
	if (cambio && funcionCambio) {
		funcionCambio(NULL, this);
	}
	return true;
};
int Material::saveState(std::vector<unsigned char>* data, bool withID) {
	int longitud = 0;
	if (withID) {
		Serializer::serialize(data, this);
	};
	//Color albedo
	Serializer::serialize(data, ambient[0], ambient[1], ambient[2], ambient[3]);
	unsigned int l = textures.size();
	Serializer::serialize(data, l);
	for (auto t : textures) {
		t->saveState(data, withID);
	}
	return longitud;
};
void Material::restoreState(std::vector<unsigned char>* data, bool withID) {
	if (data != 0) {
		Deserializer::stackBytes(data);
	}
	unsigned int l;
	if (ambient == NULL) {
		ambient = new float[4];
	}
	Deserializer::deserialize(&ambient[0], &ambient[1], &ambient[2], &ambient[3]);
	Deserializer::deserialize(&l);
	if (l < 10) {
		for (int i = 0; i < l; i++) {
			Texture* t = new Texture();
			t->restoreState(data, withID);
			textures.push_back(t);
		}
		
	}
	if (data != 0) {
		Deserializer::unstackBytes();
	}
	//funcionCambio(NULL, this);
};