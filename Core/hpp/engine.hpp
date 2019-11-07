#ifndef ENGINE_CORE_HPP
#define ENGINE_CORE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>
#include <memory>
#include <random>
#include <iostream>

#include "object.hpp"
#include "../../ResourceMgrs/gfxMgr/hpp/gfxMgr.hpp"
#include "../../ResourceMgrs/eventMgr/hpp/eventMgr.hpp"
#include "../../ResourceMgrs/stateMgr/hpp/stateMgr.hpp"
#include "../../ResourceMgrs/fontMgr/hpp/fontMgr.hpp"
#include "../../ResourceMgrs/audioMgr/hpp/audioMgr.hpp"

class Engine
{
public:
    Engine();
    ~Engine();
    void run();
    void stop();
    static void pushState(State*);
    static void popState();
    static State* getState();
    static bool isRunning();
    static sf::RenderWindow& getWindow();
protected:
    //void init();
    void physics();
    void render();
    //void cleanup();

    static bool running;

    constexpr static unsigned int ups = 60;
    constexpr static unsigned int rps = 60;

    static std::shared_ptr<sf::RenderWindow> window;
    static std::shared_ptr<GfxMgr> gfxMgr;
    static std::shared_ptr<EventMgr> eventMgr;
    static std::shared_ptr<StateMgr> stateMgr;
    static std::shared_ptr<AudioMgr> audioMgr;
    static std::shared_ptr<FontMgr> fontMgr;
private:
};


#endif // ENGINE_CORE_HPP

