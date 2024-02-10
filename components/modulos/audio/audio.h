#ifndef __AUDIO_COMPONENTE
#define __AUDIO_COMPONENTE
#include "../../src/component.h"
#include "../../src/transform.h"
#include "../../src/exportar.h"
#include "../../../modules/src/module.h"
#include "../../../modules/audio/audio.h"

class EXPORTAR_COMPONENTE Audio : public Component {
protected:
	int saveState_interno(std::vector<unsigned char>* data, bool withID = false);
	void restoreState_interno(std::vector<unsigned char>* data = 0, bool withID = false, int pos = -1);
private:
public:

	~Audio();
	Transform * transform();
	bool play(const char* file);
	bool stop();
	bool pause();
	bool resume();
	virtual void destroy();
	void setPosition(float x, float y, float z);
	void setVolume(float volume);
	TYPE_OBJECT_SERIALIZABLES getType() { return TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_AUDIO; };
};
#endif // !__AUDIO_COMPONENTE
