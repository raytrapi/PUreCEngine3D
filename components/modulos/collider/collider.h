#ifndef _COMP_COLLIDER
#define _COMP_COLLIDER

#include <vector>
#include <cmath>
#include <iostream>

#define M_PI           3.14159265358979323846
#define M_PI2          1.57079632679489661923
#define M_2PI          6.28318530717958647692
class EXPORTAR_COMPONENTE Collider : public Component {
private:
	float cX, cY, cZ;
	float longitud=0;
	std::vector<float *> vertices;
	std::vector<std::vector<float*>> caras;
	bool esCopia = false;
	
public:
	Collider() {
		cX = 0;
		cY = 0;
		cZ = 0;
	}
	Collider(Collider& c) {
		esCopia = true;
		cX = c.cX;
		cY = c.cY;
		cZ = c.cZ;
		longitud = c.longitud;
		for (auto it = c.vertices.begin(); it != c.vertices.end(); it++) {
			vertices.push_back((*it));
		}
	}
	void setVertices(std::vector<float*>* vertices);
	void setFaces(std::vector< std::vector<float*>>* faces);
	friend std::ostream& operator<<(std::ostream& os, Collider &c) {
		os << "Centro ("<<c.cX << ", " << c.cY << ", " << c.cZ << ") Radio " << c.longitud;
		return os;
	};
	~Collider() {
		if (!esCopia) {

			for (auto it = vertices.begin(); it != vertices.end(); it++) {
				delete[](*it);
			}
		} 
		vertices.clear();
	}
};


#endif // !_COMP_COLLIDER

