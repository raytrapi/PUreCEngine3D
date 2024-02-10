#include "code.h"
#include "../../modules/tape/tape.h"
#include "../../utilidades/supervisor/src/reflexivo.h"



bool Code::interfazImGUI_C(ImGuiContext* imgui){
	//ImGui::SetCurrentContext(imgui);
	ImGui::TableNextRow();
	ImGui::TableNextColumn();

	ImGui::Text(U8(Código));
	ImGui::TableNextColumn();
	ImGui::Text(nombreCodigo.c_str());
	if (codigoBase) {
		//ImGui::Text("Clase");
		//ImGui::TableNextColumn();
		//ImGui::Text(nombreCodigo.c_str());
		auto propiedades = codigoBase->getParameters();
		if (propiedades.size()) {
			for (auto p : propiedades) {
				ImGui::TableNextRow();
				ImGui::TableNextColumn();

				ImGui::Text(p.nombre.c_str());
				ImGui::TableNextColumn();
			}
		}
	}
	return true;
}

Code::~Code() {
	//DBG("Borro Code"); 
}

CodeBase* Code::linkDirectClass(CodeBase* codigoBase, void* parent) {
	modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
	this->codigoBase = codigoBase;
	if (codigoBase) {
		codigoBase->init();

		//DBG("Entidad ... ", entidad);
		codigoBase->setEntity(entidad);
		codigoBase->setParent(parent);
		codigoBase->setInput(g->getInput());
		codigoBase->setGlobal(g->getGlobal());
		codigoBase->setGraphic(g);
	}
	return codigoBase;
}

std::string Code::getName() {
	if (codigoBase) {
		return nombreCodigo;
	}
	return "Codigo Base";
}
void Code::setName(const char* n) { 
	nombreCodigo = n; 
	COPY_CHAR(n, nombre);
	
}
void Code::unlinkCodeBase(){
	if (codigoBase) {
		delete codigoBase;
		codigoBase = 0;
	}
}

void Code::relinkCodeBase(){
	modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
	unlinkCodeBase();
	linkDirectClass(g->getGlobal()->cartucho->createCodeBase(nombreCodigo.c_str()));
}
std::string Code::serializar() {
	std::string objetoSerializado = "";
	if (codigoBase) {
		objetoSerializado += GenericFile::serializate("nombreCodigoBase", nombreCodigo, false);
		std::string objetoSerializado2 = "";
		auto parametros = codigoBase->getParameters();
		for (auto p : parametros) {
			switch (p.tipo){
				case TIPO_PARAMETRO::PROP:
					if (p.variable) {
						switch (p.magnitud) {
							//0:"int", 1:"char", 2:"float", 3:"double", 4:"int* ", 5:"float* ", 6:"double* ", 7:"char* ", 8:"int** ", 9:"float** ", 10:"double** ", 11:"char** "

							case 0:
								objetoSerializado2 += (objetoSerializado2.length() > 0) ? "," : "";
								objetoSerializado2 += GenericFile::serializate(p.nombre.c_str(), std::to_string(*((int*)p.variable)),false);
								break;
							case 1:
								objetoSerializado2 += (objetoSerializado2.length() > 0) ? "," : "";
								objetoSerializado2 += GenericFile::serializate(p.nombre.c_str(), std::to_string(*((char*)p.variable)), false);
								break;
							case 2:
								objetoSerializado2 += (objetoSerializado2.length() > 0) ? "," : "";
								objetoSerializado2 += GenericFile::serializate(p.nombre.c_str(), std::to_string(*((float*)p.variable)), false);
								break;
							case 3:
								objetoSerializado2 += (objetoSerializado2.length() > 0) ? "," : "";
								objetoSerializado2 += GenericFile::serializate(p.nombre.c_str(), std::to_string(*((double*)p.variable)), false);
								break;
								//TODO: Continuar con el resto
							default:
								break;
						}

					}
				default:
					break;
			}
			

		}
		if (objetoSerializado2.length() > 0) {
			objetoSerializado += "," + GenericFile::serializate("codigoBase", "{" + objetoSerializado2 + "}",false,false);
		}
	}
	if (objetoSerializado.length()) {
		objetoSerializado = GenericFile::serializate("objeto", "{" + objetoSerializado + "}", false, false);
	}
	std::string resultado = GenericFile::serializate("componente", "{\r\n" + GenericFile::serializate("tipo", TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_CODE) + objetoSerializado + "}\r\n", false, false);
	return resultado;
}


int Code::desserializar(std::string s, int pos) {
	return 0;
}
int Code::saveState_interno(std::vector<unsigned char>* data, bool withID) {
	int longitud = Serializer::serialize(data, (int)TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_CODE);
	if (withID) {
		Serializer::serialize(data, this);
	}
	//Este es peliagudo así que lo congelamos
	std::vector<unsigned char> data2;
	Serializer::serialize(&data2, nombreCodigo.c_str());

	Serializer::serialize(data, &data2);
	return longitud;
};
void Code::restoreState_interno(std::vector<unsigned char>* data, bool withID, int pos) {
	Code* c;
	if (withID) {
		Deserializer::deserialize(&c);
	}
	//Se supone que está congelado
	unsigned int l;
	Deserializer::deserialize(&l);
	std::vector<unsigned char> data2;
	Deserializer::extract(&data2, l);

	Deserializer::stackBytes(&data2);
	char* nC = NULL;
	Deserializer::deserialize(&nC);
	if (nC) {
		setName(nC);
		//nombreCodigo = std::string(nC);
	}
	Deserializer::unstackBytes();

};
