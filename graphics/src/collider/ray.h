#ifndef __COLL_RAY
#define __COLL_RAY
#include <log.h>
#include <vector>
#include <math.h>
#include "../components/src/entity.h"
#include "../components/modulos/collider/collider.h"


namespace collider {
	
	class EXPORTAR_UTILIDADES Ray {
		private:
		public:
			static std::vector<Hit> trace(float xOrigin, float yOrigin, float zOrigin, float xDirection, float yDirection, float zDirection, float distance );
	};
};

#endif // !__COLL_RAY
