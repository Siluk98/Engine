#include "../hpp/audioMgr.hpp"
#include <SFML/Audio.hpp>
#include <iostream>

AudioMgr::AudioMgr()
{

}

AudioMgr::~AudioMgr()
{

}

void AudioMgr::loadMusicFromFile(std::string file)
{
    /*
    sf::Music* m = new sf::Music;
    if(!m->openFromFile(file))
    {
        music = nullptr;
    }
    else
    {
        music = m;
    }
    */
    if(!music.openFromFile(file))
    {
        std::cout << "Broke" << std::endl;
    }
    else
    {
        std::cout << "music.status(): " << music.getStatus() << std::endl;
    }
}

void AudioMgr::loadSoundFromFile(std::string file, std::string name)
{
    sf::SoundBuffer buffer;
    if(buffer.loadFromFile(file))
    {
        sf::Sound* s = new sf::Sound;
        s->setBuffer(buffer);
        sounds[name] = s;
    }
}

void AudioMgr::playMusic()
{
    //if(music)
        music.play();
}

void AudioMgr::playSound(std::string name)
{
    if(sounds.find(name)!=sounds.end())
    {
        sounds[name] -> play();
    }
}
