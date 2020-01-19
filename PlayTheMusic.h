#ifndef PLAYTHEMUSIC_H
#define PLAYTHEMUSIC_H

#include <string>
#include <SDL2/SDL.h>

struct AudioData
{
    Uint8 *pos;
    Uint32 length;
};

class PlayTheMusic
{
    public:
        PlayTheMusic();
        virtual ~PlayTheMusic();

        bool Play(const char *path);

        std::string GetError() {return sError;}

    protected:
        std::string sError;
    private:

    static void AudioCallback(void *userdata, Uint8 *stream, int streamLength);

};

#endif // PLAYTHEMUSIC_H
