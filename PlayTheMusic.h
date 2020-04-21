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

        virtual ~PlayTheMusic();

        bool Play(const char *path);
        void Stop();

        std::string GetError() {return sError;}

        static PlayTheMusic *Instance();
        static void DestroyInstance();

    protected:
        std::string sError;
    private:
    	static PlayTheMusic *instance;

    	PlayTheMusic();

    	bool playing;

    static void AudioCallback(void *userdata, Uint8 *stream, int streamLength);

};

#endif // PLAYTHEMUSIC_H
