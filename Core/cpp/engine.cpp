#include "../hpp/engine.hpp"

std::shared_ptr<sf::RenderWindow> Engine::window(new sf::RenderWindow(sf::VideoMode(600,600),"WINDOW"));
std::shared_ptr<GfxMgr> Engine::gfxMgr(new GfxMgr);
std::shared_ptr<EventMgr> Engine::eventMgr(EventMgr::getInstance());
std::shared_ptr<StateMgr> Engine::stateMgr(new StateMgr);
std::shared_ptr<AudioMgr> Engine::audioMgr(new AudioMgr);
std::shared_ptr<FontMgr> Engine::fontMgr(FontMgr::getInstance());
bool Engine::running = false;

Engine::Engine()
{
    std::cout << __FILE__   << ":" << __LINE__ << "Engine created" << std::endl;
}

Engine::~Engine()
{
    std::cout << __FILE__   << ":" << __LINE__ << "Engine deleted" << std::endl;
}

void Engine::stop()
{
    running = false;
}

void Engine::run()
{
    //init();

    running = true;
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    std::chrono::nanoseconds uacc(0);
    std::chrono::nanoseconds racc(0);
    std::chrono::nanoseconds tpu(1000000000);
    std::chrono::nanoseconds tpr(1000000000);
    tpu/=ups;
    tpr/=rps;
    sf::ContextSettings settings;

    while (isRunning())
    {
        begin = std::chrono::steady_clock::now();

        //window events
        events();

        //physics
        while (uacc >= tpu)
        {
            physics();
            uacc -= tpu;
        }

        //render
        while (racc >= tpr)
        {
            window->clear();
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
    sf::RenderWindow& ret = *window;
    return ret;
    //return window;
}

bool Engine::isRunning()
{
    return running;
}

void Engine::pushState(State* s)
{
    stateMgr->pushState(s);
}

void Engine::popState()
{
    stateMgr->popState();
    if(getState()==nullptr) stop();
}

void Engine::physics()
{
    if(getState()!=nullptr)
        getState()->update();
}

void Engine::render()
{
    if(getState()!=nullptr)
    {
        getState()->render(getWindow());
        getWindow().display();
    }

}

void Engine::events()
{
    if(getState()!=nullptr)
        getState()->handleEvents(getWindow());
}

State* Engine::getState()
{
    return stateMgr->getState();
}
