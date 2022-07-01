#ifndef _ENTITY_LOG
#define _ENTITY_LOG
#include <sstream>
#include "../motorExport.h"
#include "../../utilidades/log/log.h"
#include "../../components/src/entity.h"
#include "../renderable/text.h"
#include "../../utilidades/global/input.h"
namespace utiles {
	class EXPORTAR_MODULO_GRAFICO LogEntity : public Log {
		void init() {};
		void destroy() {};
	public:
		void escribirVirtual(std::string& s, utiles::Log::NIVEL nivel = utiles::Log::NIVEL::INF);
	};
}

#endif // !_ENTITY_LOG