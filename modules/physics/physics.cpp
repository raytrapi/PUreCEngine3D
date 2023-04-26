#include "physics.h"
#include <math.h>
namespace modules {
	namespace engine {
		std::tuple<float, float, float> Physics::getNormal(float x, float y, float z) {
			//Calculamos la normal del vector //Calculating the normal of the vector
			float modulo = std::sqrtf(x * x + y * y + z * z);
			if (modulo == 0) {
				return {0.0f, 0.0f, 0.0f};
			}
			return { x / modulo, y / modulo, z / modulo };

		};
		float Physics::getMagnitude(float x, float y, float z) {
			return  std::sqrtf(x * x + y * y + z * z);
		};

		
	}
}