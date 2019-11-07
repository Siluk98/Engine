#include "../hpp/engine.hpp"

std::shared_ptr<GfxMgr> Engine::gfxMgr;
std::shared_ptr<EventMgr> Engine::eventMgr;
std::shared_ptr<StateMgr> Engine::stateMgr;
std::shared_ptr<AudioMgr> Engine::audioMgr;
std::shared_ptr<FontMgr> Engine::fontMgr;

Engine::Engine()
{
    std::cout << __FILE__   << ":" << __LINE__ << "Engine created" << std::endl;
}

Engine::~Engine()
{
    std::cout << __FILE__   << ":" << __LINE__ << "Engine deleted" << std::endl;
}

void Engine::run()
{
    //init();

    bool isRunning = true;
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    std::chrono::nanoseconds uacc(0);
    std::chrono::nanoseconds racc(0);
    std::chrono::nanoseconds tpu(1000000000);
    std::chrono::nanoseconds tpr(1000000000);
    tpu/=ups;
    tpr/=rps;
    sf::ContextSettings settings;

    while (isRunning)
    {
        begin = std::chrono::steady_clock::now();

        //window events
        if(stateMgr->getState()!=nullptr)
        stateMgr->getState()->handleEvents(*window);

        //physics
        while (uacc >= tpu)
        {
            physics();
            uacc -= tpu;
        }

        //render
        while (racc >= tpr)
        {
            render();
            racc -= tpr;
        }
        end = std::chrono::steady_clock::now();
        uacc += (end - begin);
        racc += (end - begin);
    }

    //cleanup();
}

sf::RenderWindow& Engine::getWindow()
{
    return window;
}
