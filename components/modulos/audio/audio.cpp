#include "audio.h"



Audio::~Audio() {
   //DBG("-Borramos componente Audio");
   stop();
}

Transform* Audio::transform() { 
   return nullptr;
}

bool Audio::play(const char* file) {
   modules::Audio* audio = modules::Audio::get<modules::Audio>();
   //DBG("Itento reproducir dentro de Componente");
   if (audio) {
      return audio->play(file);
   }
   return false;
}

bool Audio::stop() {
   modules::Audio* audio = modules::Audio::get<modules::Audio>();
   //DBG("Itento reproducir dentro de Componente");
   if (audio) {
      return audio->stop();
   }
   return false;
}

bool Audio::pause() {
   modules::Audio* audio = modules::Audio::get<modules::Audio>();
   //DBG("Itento reproducir dentro de Componente");
   if (audio) {
      return audio->pause();
   }
}

bool Audio::resume() {
   modules::Audio* audio = modules::Audio::get<modules::Audio>();
   //DBG("Itento reproducir dentro de Componente");
   if (audio) {
      return audio->resume();
   }
}
void Audio::setPosition(float x, float y, float z) {
   modules::Audio* audio = modules::Audio::get<modules::Audio>();
   if (audio) {
      audio->setPosition(x,y,z);
   }
}
void Audio::setVolume(float volume) {
   modules::Audio* audio = modules::Audio::get<modules::Audio>();
   if (audio) {
      audio->setVolume(volume);
   }
}
void Audio::destroy() {
   //DBG("DESTRUYO");
}
int Audio::saveState_interno(std::vector<unsigned char>* data, bool withID) {
   int longitud=Serializer::serialize(data, (int)TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_AUDIO) ;
   return longitud;
};
void Audio::restoreState_interno(std::vector<unsigned char>* data, bool withID, int pos) {
};