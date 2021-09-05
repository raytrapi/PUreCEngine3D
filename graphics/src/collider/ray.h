#ifndef __COLL_RAY
#define __COLL_RAY
#include <log.h>
#include <vector>
#include "../components/src/entity.h"


namespace collider {
	struct EXPORTAR_UTILIDADES Hit {

	};
	class EXPORTAR_UTILIDADES Ray {
		private:
		public:
			static std::vector<Hit> trace(float xOigin, float yOigin, float zOigin, float xTarget, float yTarget, float zTarget, float distance );
	};
};

#endif // !__COLL_RAY
