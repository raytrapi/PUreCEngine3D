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

		void Physics::TraceImpl(const char* inFMT, ...) {
			// Format the message
			va_list list;
			va_start(list, inFMT);
			char buffer[1024];
			vsnprintf(buffer, sizeof(buffer), inFMT, list);
			va_end(list);

			// Print to the TTY
			DBG(buffer);
		}
		bool Physics::AssertFailedImpl(const char* inExpression, const char* inMessage, const char* inFile, unsigned int inLine) {
			// Print to the TTY
			ERR("%:%:(%) %", inFile, inLine, inExpression, (inMessage != nullptr ? inMessage : ""));
			return true;
		};

	}
}