#ifndef _PYSHICS_1_0
#define _PYSHICS_1_0

#include <physics.h>
#include <entity.h>
#include <transform.h>
class Physics10 : public modules::engine::Physics {
public:
	char* nombre() { return (char*)"F�sicas 1.0"; };

	void update();
};


#endif // !_PYSHICS_1_0
