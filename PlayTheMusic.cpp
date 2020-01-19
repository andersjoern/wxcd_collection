#include "PlayTheMusic.h"

PlayTheMusic::PlayTheMusic()
{
    //ctor
}

PlayTheMusic::~PlayTheMusic()
{
    //dtor
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

void PlayTheMusic::AudioCallback(void *userdata, Uint8 *stream, int streamLength)
{
    AudioData *audio = (AudioData *)userdata;

    if (audio->length == 0)
    {
        return;
    }
    Uint32 length = (Uint32)streamLength;
    length = (length > audio->length ? audio->length : length);
    SDL_memcpy(stream, audio->pos, length);
    audio->pos += length;
    audio->length -= length;
}

bool PlayTheMusic::Play(const char *path)
{
    sError = "";
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        sError = SDL_GetError();
        return false;
    }
    SDL_AudioSpec wavSpec;
    Uint8 *wavStart;
    Uint32 wavLength;

    if (SDL_LoadWAV(path, &wavSpec, &wavStart, &wavLength) == NULL)
    {
        sError = std::string("Cannot open file: ") + std::string(path);
        return false;
    }

    AudioData audio;
    audio.pos = wavStart;
    audio.length = wavLength;

    wavSpec.callback = AudioCallback;
    wavSpec.userdata = &audio;

    SDL_AudioDeviceID device = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

    if (device == 0)
    {
        sError = SDL_GetError();
        return false;
    }

    SDL_PauseAudioDevice(device, 0);

    while (audio.length > 0)
    {
        SDL_Delay(100);
    }

    SDL_CloseAudioDevice(device);
    SDL_FreeWAV(wavStart);
    SDL_Quit();

    return true;
}
