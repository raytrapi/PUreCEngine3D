#include "logEntity.h"
namespace utiles {
	void LogEntity::escribirVirtual(std::string& s, utiles::Log::NIVEL nivel) {
		
		std::time_t ahora = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());


		std::stringstream os;
		switch (nivel) {
		case utiles::Log::FAT:
			os << "FAT\t";
			break;

		case utiles::Log::ERR:
			os << "ERR\t";
			break;
		case utiles::Log::WAR:
			os << "WAR\t";
			break;
		case utiles::Log::INF:
			os << "INF\t";
			break;
		case utiles::Log::DEB:
			os << "DEB\t";
			break;
		}

		if (os) {
			os << std::put_time(std::localtime(&ahora), "%F %T%z") << "\t" << s << std::endl;
		}

		/*Entity* entidad = Entity::create<Entity::TYPE::EMPTY>(1);
		RenderableComponent* rend = entidad->addComponent<RenderableComponent>();
		renderable::Text* texto = rend->add<renderable::Text>();
		texto->setText(os.str().c_str());
		*/
	}
}