#include "loadLevel.h"
#include "../components/modulos/code/code.h"


int LoadLevel::load(std::vector<unsigned char> *datos, int pos, modules::graphics::Graphic* m, unsigned int version) {
	switch (version) {
		case 1:
		{
			//Ahora procesamos
			Deserializer::setBytes(datos);
			//Primero leemos la información del mundo
			int longitud = 0;
			Deserializer::deserialize(&longitud);
			//Recuperamos el dato
			std::vector<unsigned char> datosMundo;
			Deserializer::extract(&datosMundo, longitud);
			Deserializer::stackBytes(&datosMundo);
			Deserializer::deserialize(&m->getGlobal()->iLA);
			float x, y, z, w;
			Deserializer::deserialize(&m->getGlobal()->rLA);
			Deserializer::deserialize(&m->getGlobal()->gLA);
			Deserializer::deserialize(&m->getGlobal()->bLA);
			Deserializer::deserialize(&w);
			//Ahora la Camara
			auto camara = m->getActiveEditorCamera();
			if (camara) {
				//camara->restoreState();
				Deserializer::deserialize(&x, &y, &z);
				camara->transform()->setPosition(x, y, z);
				Deserializer::deserialize(&x, &y, &z);
				camara->transform()->setRotation(x, y, z);
				Deserializer::deserialize(&x, &y, &z);
				camara->transform()->setScale(x, y, z);
				camara->transformChanged();
			} else {
				Deserializer::setPos(Deserializer::getPos() + 9*sizeof(float));
			}
			Deserializer::unstackBytes();
			while (!Deserializer::end()) {
				Entity* entidad = new Entity();
				entidad->graphic=m;
				entidad->restoreState();
			}
		}
		break;
	}
	return 0;
}
int LoadLevel::load(std::string s, int pos, modules::graphics::Graphic* m, unsigned int version) {
	switch(version) {
		case 1:
			{
				std::vector<unsigned char> datos;
				for (auto c : s) {
					datos.push_back(c); //Cargamos los datos, quizás esto lo podemos mejorar en el futuro
				}
				//Ahora procesamos
				Deserializer::setBytes(&datos);
				Deserializer::deserialize(&m->getGlobal()->iLA);
				float x, y, z, w;
				Deserializer::deserialize(&m->getGlobal()->rLA);
				Deserializer::deserialize(&m->getGlobal()->gLA);
				Deserializer::deserialize(&m->getGlobal()->bLA);
				Deserializer::deserialize(&w);
				//Ahora la Camara
				auto camara = m->getActiveEditorCamera();
				if (camara) {
					Deserializer::deserialize(&x, &y, &z);
					camara->transform()->setPosition(x, y, z);
					Deserializer::deserialize(&x, &y, &z);
					camara->transform()->setScale(x, y, z);
					Deserializer::deserialize(&x, &y, &z);
					camara->transform()->setRotation(x, y, z);
					camara->transformChanged();
				}
				while (!Deserializer::end()) {
					Entity* entidad = new Entity();
					entidad->restoreState();
				}
			}
			break;
		default:
			char caracteresNoValidos[] = { '\r','\n' };
			s = GenericFile::eraseCharacters(s, caracteresNoValidos);
			while (pos < s.length()) {
				//Es un objeto
				auto [posT, clave, valor] = GenericFile::unserializate(s, pos + 1);
				pos = posT;
				if (clave == "luz") {
					//proceso la luz
					int posL = 0;
					while (posL < valor.length()) {
						auto [posLT, claveL, valorL] = GenericFile::unserializate(valor, posL);
						posL = posLT;
						if (claveL == "intensidad") {
							m->getGlobal()->iLA = GenericFile::unserializatef(valorL);
						} else if (claveL == "color") {
							auto [r, g, b, a] = GenericFile::unserializate4f(valorL);
							m->getGlobal()->rLA = r;
							m->getGlobal()->gLA = g;
							m->getGlobal()->bLA = b;
						}
					}
				} else if (clave == "camara") {
					//proceso la camara
					int posL = 0;
					while (posL < valor.length()) {
						auto [posLT, claveL, valorL] = GenericFile::unserializate(valor, posL);
						posL = posLT;
						if (claveL == "posicion") {
							auto camara = m->getActiveEditorCamera();
							if (camara) {
								auto [x, y, z] = GenericFile::unserializate3f(valorL);
								camara->transform()->setPosition(x, y, z);
								camara->transformChanged();
							}
						}
					}
				} else if (clave == "entidades") {
					desserializarEntidades("[" + valor + "]", 0, m);
				}
				//pos++;
				//DBG("%", valor);

			}
			return pos;
	}
	

}
int LoadLevel::desserializarEntidades(std::string s, int pos, modules::graphics::Graphic* m) {
	while (pos < s.length()) {
		switch (s[pos]) {
		case '[':
		case ',':
		{
			Entity* entidad = new Entity();
			entidad->graphic = m;
			pos = GenericFile::jumpSerializateTo('{', s, pos + 1);
			while (pos < s.length() && s[pos] != '}') {
				auto [posT, clave, valor] = GenericFile::unserializate(s, pos);
				pos = posT;
				if (clave == "name") {
					entidad->setName(valor);
					entidad->setName(valor);
				} else if (clave == "active") {
					entidad->setActive(valor == "S");
				} else if (clave == "trans_position") {
					auto [x, y, z] = GenericFile::unserializate3f(valor);
					entidad->transformada->setPosition(x, y, z);
				} else if (clave == "trans_scale") {
					auto [x, y, z] = GenericFile::unserializate3f(valor);
					entidad->transformada->setScale(x, y, z);
				} else if (clave == "trans_rotation") {
					auto [x, y, z] = GenericFile::unserializate3f(valor);
					entidad->transformada->setRotation(x, y, z);
				} else if (clave == "componente") {
					//DBG("C %", valor);
					desserializarComponente(valor, 0, entidad);

					//pos = GenericFile::jumpSerializateTo('}', s, pos + 1);
					//pos += valor.length();

				} else {
					pos++;
				}
			}
			pos++;
		}
		break;		
		default:
			pos++;

		}
	}
	return pos;
}
int LoadLevel::desserializarComponente(std::string s, int pos, Entity* e){
	Component* c = NULL;
	TYPE_OBJECT_SERIALIZABLES t;
	while (pos < s.length()) {
		auto [posT, clave, valor] = GenericFile::unserializate(s, pos);
		pos = posT;
		if (clave == "tipo") {
			t = (TYPE_OBJECT_SERIALIZABLES)std::atoi(valor.c_str());
			switch (t) {
				case TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_RENDERABLE:
				{
					c = e->addComponent<RenderableComponent>();

				}
				break;
				case TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_LUZ:
				{

					
					c=e->addComponent<LightComponent>();
					auto shaders = e->addComponent<graphics::ShaderComponent>();
					shaders->loadShader("shaders/gizmo_vertex_mesh.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
					shaders->loadShader("shaders/gizmo_fragment_mesh.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
					shaders->loadShader("shaders/shadow_map_vertex_dbg.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
					shaders->loadShader("shaders/shadow_map_fragment_dbg.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
					shaders->loadShader("shaders/editor/entidadID_vertex.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
					shaders->loadShader("shaders/editor/entidadID_fragment.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
					((LightComponent*)c)->transformChanged();
				}
				break;
				case TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_RIGIDBODY:
				{
					c = e->addComponent<physics::RigidBodyComponent>();
					
				}
				break;
				case TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_BOXCOLLIDER:
				{
					//c = e->addComponent<BoxCollider>();

				}
				break;
				case TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_CODE:
				{
					//c = (Component*)e->addComponent<Code>();
					


				}
				break;
				default:
					ERR("No se reconoce el tipo de Componente [Tipo: %]", (int)t);
					return  s.length();
					break;
			}
		} else if (clave == "objeto") {
			//Averiguo el tipo: t
			//Hago que el componente se desserialice

			auto [posTO, claveO, valorO] = GenericFile::unserializate(valor, 0);
			if (claveO == "tipo") {
				int t = std::atoi(valorO.c_str());

				switch ((renderable::Object::TYPE)t) {
					case renderable::Object::TYPE::CUBE:
						auto o = ((RenderableComponent*)c)->add<renderable::Cube>();
						o->desserializar(valorO, posTO);
						((RenderableComponent*)c)->setUpdated(true);
						//e->desserializarObjeto<renderable::Cube, RenderableComponent>(valor, posTO, (RenderableComponent*)c);
						break;
					}/**/
					//c->desserializar(valor, 0);
			}
			pos += valor.length() + 2;
		} else {
			pos = s.length();
		}
	}
	return pos;
	
}
