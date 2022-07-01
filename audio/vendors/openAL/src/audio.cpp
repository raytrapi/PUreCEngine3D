#include "audio.h"

char* AudioAL::load_wav(const std::string& filename, std::uint8_t& channels, std::int32_t& sampleRate, std::uint8_t& bitsPerSample, ALsizei& size) {
   std::ifstream in(filename, std::ios::binary);
   if (!in.is_open()) {
      DBG("ERROR AUDIO: No se puede abrir el fichero \"%\"", filename);
      return nullptr;
   }
   if (!load_wav_file_header(in, channels, sampleRate, bitsPerSample, size)) {
      DBG("ERROR AUDIO: No se puede cargar la cabecera wav de \"%\"",filename);
      return nullptr;
   }

   char* data = new char[size];

   in.read(data, size);

   return data;
}

bool AudioAL::get_available_devices(std::vector<std::string>& devicesVec, ALCdevice* device) {
   const ALCchar* devices=alcGetString(nullptr,ALC_DEVICE_SPECIFIER);
   if (!devices)
      return false;

   const char* ptr = devices;

   devicesVec.clear();

   do {
      devicesVec.push_back(std::string(ptr));
      ptr += devicesVec.back().size() + 1;
   } while (*(ptr + 1) != '\0');

   return true;
}
ALsizei AudioAL::load_wav_file_header(std::ifstream& file, HeaderWAV & header) {
   char buffer[4];
   if (!file.is_open())
      return 0;

   // the RIFF
   if (!file.read(buffer, 4)) {
      DBG("ERROR AUDIO: could not read RIFF");
      return 0;
   }
   if (std::strncmp(buffer, "RIFF", 4) != 0) {
      DBG("ERROR AUDIO: file is not a valid WAVE file (header doesn't begin with RIFF)");
      return 0;
   }

   // the size of the file
   if (!file.read(buffer, 4)) {
      DBG("ERROR AUDIO: could not read size of file");
      return 0;
   }

   // the WAVE
   if (!file.read(buffer, 4)) {
      DBG("ERROR AUDIO: could not read WAVE");
      return 0;
   }
   if (std::strncmp(buffer, "WAVE", 4) != 0) {
      DBG("ERROR AUDIO: file is not a valid WAVE file (header doesn't contain WAVE)");
      return 0;
   }
   for (int i = 0; i < 4; i++) {
      header.format[i] = buffer[i];
   }
   
   // "fmt/0"
   if (!file.read(buffer, 4)) {
      DBG("ERROR AUDIO: could not read fmt/0");
      return 0;
   }
   for (int i = 0; i < 4; i++) {
      header.subchunk1_id[i] = buffer[i];
   }
   
   // this is always 16, the size of the fmt data chunk
   if (!file.read(buffer, 4)) {
      DBG("ERROR AUDIO: could not read the 16");
      return 0;
   }
   header.subchunk1_size = convert_to_int(buffer, 4); 

   // PCM should be 1?
   if (!file.read(buffer, 2)) {
      DBG("ERROR AUDIO: could not read PCM");
      return 0;
   }
   header.audio_format = convert_to_int(buffer, 4);
   
   // the number of channels
   if (!file.read(buffer, 2)) {
      DBG("ERROR AUDIO: could not read number of channels");
      return 0;
   }
   header.num_channels = convert_to_int(buffer, 2);

   // sample rate
   if (!file.read(buffer, 4)) {
      DBG("ERROR: could not read sample rate");
      return 0;
   }
   header.sample_rate = convert_to_int(buffer, 4);

   // (sampleRate * bitsPerSample * channels) / 8
   if (!file.read(buffer, 4)) {
      DBG("ERROR AUDIO: could not read (sampleRate * bitsPerSample * channels) / 8");
      return 0;
   }
   header.byte_rate = convert_to_int(buffer, 4);

   // ?? dafaq
   if (!file.read(buffer, 2)) {
      DBG("ERROR AUDIO: could not read dafaq");
      return 0;
   }
   header.block_align= convert_to_int(buffer, 2);

   // bitsPerSample
   if (!file.read(buffer, 2)) {
      DBG("ERROR AUDIO: could not read bits per sample");
      return 0;
   }
   header.bits_per_sample = convert_to_int(buffer, 2);

   // data chunk header "data"
   if (!file.read(buffer, 4)) {
      DBG("ERROR AUDIO: could not read data chunk header");
      return 0;
   }
   if (std::strncmp(buffer, "data", 4) != 0) {
      DBG("ERROR AUDIO: file is not a valid WAVE file (doesn't have 'data' tag)");
      return 0;
   }
   for (int i = 0; i < 4; i++) {
      header.subchunk2_id[i] = buffer[i];
   }
   // size of data
   if (!file.read(buffer, 4)) {
      DBG("ERROR AUDIO: could not read data size");
      return 0;
   }
   header.subchunk2_size = convert_to_int(buffer, 4);

   /* cannot be at the end of file */
   if (file.eof()) {
      DBG("ERROR AUDIO: reached EOF on the file");
      return false;
   }
   if (file.fail()) {
      DBG("ERROR AUDIO: fail state set on the file");
      return 0;
   }

   return header.subchunk2_size;
}
bool AudioAL::load_wav_file_header(std::ifstream& file, std::uint8_t& channels, std::int32_t& sampleRate, std::uint8_t& bitsPerSample, ALsizei& size) {
   size=load_wav_file_header(file, cabecera);
   if (size > 0) {
      channels = cabecera.num_channels;
      sampleRate = cabecera.sample_rate;
      bitsPerSample = cabecera.bits_per_sample;
      return true;
   }
   return false;
}

std::int32_t AudioAL::convert_to_int(char* buffer, std::size_t len) {
   std::int32_t a = 0;
   if (std::endian::native == std::endian::little)
      std::memcpy(&a, buffer, len);
   else
      for (std::size_t i = 0; i < len; ++i)
         reinterpret_cast<char*>(&a)[3 - i] = buffer[i];
   return a;
}

AudioAL::AudioAL() {
	DBG("Cargando audio");
}

AudioAL::~AudioAL() {
	DBG("Descargando AUDIO");
   stop();
}

bool AudioAL::play(const char* file) {
	DBG("Intento ejectuar audio");


   openALDevice = alcOpenDevice(nullptr);
   if (!openALDevice)
      return 0;

   openALContext= alcCreateContext(openALDevice,nullptr);
   if (!openALContext) {
      DBG("ERROR: Could not create audio context");
      return false;
   }
   ALCboolean contextMadeCurrent = alcMakeContextCurrent(openALContext);

   if (contextMadeCurrent != ALC_TRUE) {
      DBG("ERROR: Could not make audio context current");
      return false;
   }

   std::uint8_t channels;
   std::int32_t sampleRate;
   std::uint8_t bitsPerSample;
   ALsizei longitud;
   char* soundData=load_wav(file, channels, sampleRate, bitsPerSample, longitud);

   if (!soundData) {
      DBG("ERROR: Could not load wav");
      return 0;
   }
   alGenBuffers(1,&buffer);
   ALenum format;
   if (channels == 1 && bitsPerSample == 8)
      format = AL_FORMAT_MONO8;
   else if (channels == 1 && bitsPerSample == 16)
      format = AL_FORMAT_MONO16;
   else if (channels == 2 && bitsPerSample == 8)
      format = AL_FORMAT_STEREO8;
   else if (channels == 2 && bitsPerSample == 16)
      format = AL_FORMAT_STEREO16;
   else {
      DBG("ERROR: unrecognised wave format: % channels, % bps", channels, bitsPerSample);
      return 0;
   }

   alBufferData(buffer, format, soundData, longitud, sampleRate);
   delete []soundData; // erase the sound in RAM

   
   alGenSources(1, &fuente);
   alSourcef(fuente, AL_PITCH, 1); 
   alSourcef(fuente, AL_GAIN, 1.0f);
   alSource3f(fuente, AL_POSITION, pX, pY, pZ);
   alSource3f(fuente, AL_VELOCITY, 0, 0, 0);
   alSourcei(fuente, AL_LOOPING, AL_FALSE);
   alSourcei(fuente, AL_BUFFER, buffer);
   alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
   //alSourcef(fuente, AL_V)

   tiempoAnterior = Time::time();
   alSourcePlay(fuente);

   estado = AL_PLAYING;
   duracion = (((float)cabecera.subchunk2_size / (float)(cabecera.num_channels * ((float)cabecera.bits_per_sample / 8))) / (float)cabecera.sample_rate) * 1000;
   timeout = utiles::Watchdog::setTimeOut([&] {this->stop(); }, duracion);
   


	return true;
}
void AudioAL::setPosition(float x, float y, float z) {
   pX = x;
   pY = y;
   pZ = z;
   if (fuente) {
      alSource3f(fuente, AL_POSITION, pX, pY, pZ);
      //alSourcePlay(fuente);
   }
}
void AudioAL::setVolume(float volume) {
   if (fuente) {
      alSourcef(fuente, AL_GAIN, volume);
   }
}
bool AudioAL::pause() {
   if (estado == AL_PLAYING) {
      estado = AL_PAUSED;
      tiempoEscucha = Time::diff(tiempoAnterior);
      alSourcePause(fuente);
      if (timeout != -1) {
         utiles::Watchdog::clearTimeOut(timeout);
         timeout = -1;
      }
   } else if (estado == AL_PAUSED) {
      resume();
   }
   return true;
}
bool AudioAL::resume() {
   alSourcePlay(fuente);
   estado = AL_PLAYING;
   
   tiempoAnterior = Time::time();
   timeout = utiles::Watchdog::setTimeOut([&] {this->stop(); }, duracion-tiempoEscucha);
   return false;
}
bool AudioAL::stop() {
   DBG("Paramos la música");
   
   if (timeout != -1) {
      utiles::Watchdog::clearTimeOut(timeout);
      timeout = -1;
   }
   if (estado == AL_PLAYING || estado == AL_PAUSED) {
      estado = AL_STOPPED;
      alSourceStop(fuente);
      alDeleteSources(1, &fuente);
      alDeleteBuffers(1, &fuente);

      alcMakeContextCurrent(nullptr);
      if (openALContext) {
         alcDestroyContext(openALContext);
      }
      if (openALDevice) {
         return alcCloseDevice(openALDevice);
      }
   }
   return false;
}






REGISTRAR_MODULO(AudioAL);