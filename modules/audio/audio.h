#ifndef _AUDIO
#define _AUDIO

#include "../src/module.h"
namespace modules {
	class EXPORTAR_MODULO Audio:public Module {
		public:
			Module::MODULES_TYPE tipo() { return Module::MODULES_TYPE::AUDIO; };
			
			virtual bool play(const char* file) = 0;
			virtual bool pause()=0;
			virtual bool resume() = 0;
			virtual bool stop()=0;
			virtual void setPosition(float x, float y, float z) {};
			virtual void setVolume(float volume) {};
	};

	
}


#endif //_AUDIO