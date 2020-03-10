#include "../hpp/eventMgr.hpp"
#include <iostream>
#include "../hpp/eventActions.hpp"
#include "../hpp/eventPredicates.hpp"

EventMgr* EventMgr::instance = nullptr;

EventMgr::EventMgr(){
    objectActions = new std::map<std::string, Action>;
    objectPredicates = new std::map<std::string, Predicate>;
    instance = this;
    initDefaultActions(this);
    initDefaultPredicates(this);
    std::cout << "EventMgr Const" << std::endl;
};

EventMgr::~EventMgr(){
    instance = nullptr;
    std::cout << "EventMgr Deleted" << std::endl;
};

EventMgr* EventMgr::create()
{
    if(instance != nullptr) return instance;
    return new EventMgr;
}

Predicate EventMgr::addPredicate(std::string name, Predicate pred)
{
    (*objectPredicates)[name] = pred;
    return (*objectPredicates)[name];
    //return nullptr;
}

Action EventMgr::addAction(std::string name, Action act)
{
    (*objectActions)[name] = act;
    return (*objectActions)[name];
    //return nullptr;
}

Predicate EventMgr::getPredicate(std::string name)
{
    if(objectPredicates->find(name) == objectPredicates->end())
    {
        return nullptr;
    }
    else
    {
        return (*objectPredicates)[name];
    }
}

Action EventMgr::getAction(std::string name)
{
    if(objectActions->find(name) == objectActions->end())
    {
        return nullptr;
    }
    else
    {
        return (*objectActions)[name];
    }
}

EventMgr* EventMgr::getInstance()
{
    if(instance == nullptr) instance = new EventMgr;
    return instance;
}

void EventMgr::printPredicates()
{
    for (auto it = objectPredicates->begin(); it != objectPredicates->end(); it++ )
    {
        std::cout << it->first << std::endl ;
    }
}

void EventMgr::printActions()
{
    for (auto it = objectActions->begin(); it != objectActions->end(); it++ )
    {
        std::cout << it->first << std::endl ;
    }
}
