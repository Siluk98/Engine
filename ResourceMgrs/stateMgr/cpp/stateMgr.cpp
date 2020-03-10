#include "../hpp/stateMgr.hpp"

StateMgr::StateMgr()
{
    currentState = nullptr;
}

StateMgr::~StateMgr()
{
    for(auto e: states) delete e;
    currentState = nullptr;
}

/*
void StateMgr::addState(State* s)
{
    if(findState(s->getId())!=nullptr)
    {
        states.push_back(s);
    }
}

void StateMgr::removeState(std::string arg)
{
    int i=findStateIndex(arg);
    //Memory::deallocate(sizeof(states[i]));
    if(i!=-1)
        states.erase(states.begin()+i);
}
*/

void StateMgr::pushState(State* s)
{
    states.push_back(s);
    if(currentState!=nullptr)
    currentState->pause();
    s->init();
    currentState = s;
}

void StateMgr::popState()
{
    if(!states.empty())
    {
        states.back()->cleanup();
        delete states.back();
        states.pop_back();
        if(!states.empty())
        {
            currentState = states.back();
            currentState->resume();
        }
        else currentState = nullptr;
    }
}

State* StateMgr::findState(std::string arg)
{
    for(auto i:states)
        if(i->getId() == arg)
            return i;
    return nullptr;
}

int StateMgr::findStateIndex(std::string arg)
{
    for(unsigned int it=0;it<states.size();it++)
        if(states[it]->getId() == arg)
            return it;
    return -1;
}

State* StateMgr::getState()
{
    return currentState;
}

unsigned int StateMgr::getSize()
{
    return states.size();
}
