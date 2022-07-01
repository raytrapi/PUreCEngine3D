#ifndef __AUDIO_COMPONENTE
#define __AUDIO_COMPONENTE
#include "../../src/component.h"
#include "../../src/transform.h"
#include "../../src/exportar.h"
#include "../../../modules/src/module.h"
#include "../../../modules/audio/audio.h"

class EXPORTAR_COMPONENTE Audio : public Component {
protected:

private:
public:
	Audio();
	~Audio();
	Transform * transform();
	bool play(const char* file);
	bool stop();
	bool pause();
	bool resume();
	virtual void destroy();
	void setPosition(float x, float y, float z);
	void setVolume(float volume);
};
#endif // !__AUDIO_COMPONENTE
