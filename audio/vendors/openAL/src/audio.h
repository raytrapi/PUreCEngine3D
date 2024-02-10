#ifndef _AUDIO_AL
#define _AUDIO_AL
#include <log.h>
#include "..\..\audio\src\audioBase.h"
#include <module.h>
#include <watchdog.h>
#include <timer.h>
//Librerías de openAL
#include <AL/al.h>
#include <AL/alc.h>

#define alcCall(function, device, ...) alcCallImpl(__FILE__, __LINE__, function, device, __VA_ARGS__)

bool check_alc_errors(const std::string& filename, const std::uint_fast32_t line, ALCdevice* device)
{
    ALCenum error = alcGetError(device);
    if(error != ALC_NO_ERROR)
    {
        std::cerr << "***ERROR*** (" << filename << ": " << line << ")\n" ;
        switch(error)
        {
        case ALC_INVALID_VALUE:
            std::cerr << "ALC_INVALID_VALUE: an invalid value was passed to an OpenAL function";
            break;
        case ALC_INVALID_DEVICE:
            std::cerr << "ALC_INVALID_DEVICE: a bad device was passed to an OpenAL function";
            break;
        case ALC_INVALID_CONTEXT:
            std::cerr << "ALC_INVALID_CONTEXT: a bad context was passed to an OpenAL function";
            break;
        case ALC_INVALID_ENUM:
            std::cerr << "ALC_INVALID_ENUM: an unknown enum value was passed to an OpenAL function";
            break;
        case ALC_OUT_OF_MEMORY:
            std::cerr << "ALC_OUT_OF_MEMORY: an unknown enum value was passed to an OpenAL function";
            break;
        default:
            std::cerr << "UNKNOWN ALC ERROR: " << error;
        }
        std::cerr << std::endl;
        return false;
    }
    return true;
}

template<typename alcFunction, typename... Params>
auto alcCallImpl(const char* filename, 
                 const std::uint_fast32_t line, 
                 alcFunction function, 
                 ALCdevice* device, 
                 Params... params)
->typename std::enable_if_t<std::is_same_v<void,decltype(function(params...))>,bool>
{
    function(std::forward<Params>(params)...);
    return check_alc_errors(filename,line,device);
}

template<typename alcFunction, typename ReturnType, typename... Params>
auto alcCallImpl(const char* filename,
                 const std::uint_fast32_t line,
                 alcFunction function,
                 ReturnType& returnValue,
                 ALCdevice* device, 
                 Params... params)
->typename std::enable_if_t<!std::is_same_v<void,decltype(function(params...))>,bool>
{
    returnValue = function(std::forward<Params>(params)...);
    return check_alc_errors(filename,line,device);
}
/**/
struct HeaderWAV {
   char format[4];
   char chunk_id[4];
   int chunk_size;
   char subchunk1_id[4];
   int subchunk1_size;
   short int audio_format;
   short int num_channels;
   int sample_rate;
   int byte_rate;
   short int block_align;
   short int bits_per_sample;
   char subchunk2_id[4];
   int subchunk2_size;
};
class AudioAL : public AudioBase {
private:
   std::int32_t convert_to_int(char* buffer, std::size_t len);
   ALsizei load_wav_file_header(std::ifstream& file, HeaderWAV& header);
   bool load_wav_file_header(std::ifstream& file, std::uint8_t& channels, std::int32_t& sampleRate,  std::uint8_t& bitsPerSample,      ALsizei& size);
   char* load_wav(const std::string& filename, std::uint8_t& channels,  std::int32_t& sampleRate, std::uint8_t& bitsPerSample, ALsizei& size);

	bool get_available_devices(std::vector<std::string>& devicesVec, ALCdevice* device);
   ALint estado = AL_STOPPED;
   ALuint fuente = AL_NONE;
   ALuint buffer = 0;
   ALCcontext* openALContext = 0;
   ALCdevice* openALDevice = 0;
   HeaderWAV cabecera;
   float duracion=0;
   double tiempoEscucha = 0;
   std::chrono::system_clock::time_point tiempoAnterior;
   unsigned timeout = 0;
   float pX = 0.f;
   float pY = 0.f;
   float pZ = 0.f;

public:
	AudioAL();
	~AudioAL();
	virtual char* nombre() { return (char*)"Audio OpenAL"; };

	virtual bool play(const char* file);
   virtual bool pause();
   virtual bool resume();
   virtual bool stop();
   virtual void setPosition(float x, float y, float z);
   virtual void setVolume(float volume);

};


#endif // !_AUDIO_AL
