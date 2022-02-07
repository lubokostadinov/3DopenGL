#pragma once
#include <fmod.hpp>
#include <string>
#include <map>

typedef std::map<std::string, FMOD::Sound*> SoundMap;

class AudioManager
{
public:

    AudioManager();
    ~AudioManager();

    void Update(float elapsed);

    void LoadSFX(const std::string& path);
    void LoadSong(const std::string& path);

    void PlaySFX(const std::string& path,
        float minVolume, float maxVolume,
        float minPitch, float maxPitch);

    void PlaySong(const std::string& path);

    void StopSFXs();
    void StopSongs();

    void SetMasterVolume(float volume);
    void SetSFXsVolume(float volume);
    void SetSongsVolume(float volume);

private:
    typedef std::map<std::string, FMOD::Sound*> SoundMap;
    enum Category { CATEGORY_SFX, CATEGORY_SONG, CATEGORY_COUNT };

    void Load(Category type, const std::string& path);

    FMOD::System* system;
    FMOD::ChannelGroup* master;
    FMOD::ChannelGroup* groups[CATEGORY_COUNT];
    SoundMap sounds[CATEGORY_COUNT];
    FMOD_MODE modes[CATEGORY_COUNT];

    FMOD::Channel* currentSong;
    std::string currentSongPath;
    std::string nextSongPath;

    enum FadeState { FADE_NONE, FADE_IN, FADE_OUT };
    FadeState fade;
};


