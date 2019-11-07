#ifndef AUDIOMGR_HPP
#define AUDIOMGR_HPP

#include <map>
#include <SFML/Audio.hpp>

class AudioMgr
{
public:
    AudioMgr();
    ~AudioMgr();
    void loadSoundFromFile(std::string file ,std::string name);
    void loadMusicFromFile(std::string file);
    void playMusic();
    void playSound(std::string);
    //AudioMgr* const getInstance();
private:
    std::map<std::string,sf::Sound*> sounds;
    sf::Music music;
    //AudioMgr* instance;
};

#endif
