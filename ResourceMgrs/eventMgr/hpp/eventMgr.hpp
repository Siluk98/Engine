#ifndef EVENTMGR_HPP
#define EVENTMGR_HPP

#include <functional>
#include <map>
//include "event.hpp"
#include "../../../Core/hpp/object.hpp"

//using Predicate = bool(*)(Object*,Object*, std::string, std::string);
//using Action = void(*)(Object*,Object*, std::string, std::string);
#include "../../../Core/hpp/customTypes.hpp"

class Event;
//change to singleton
class EventMgr
{
public:

    ~EventMgr();
    Predicate addPredicate(std::string, Predicate);
    Action addAction(std::string, Action);
    Predicate getPredicate(std::string);
    Action getAction(std::string);
    static EventMgr* getInstance();
    static EventMgr* create();
    void printPredicates();
    void printActions();
private:
    EventMgr();
    std::vector<Event*> events;
    std::map<std::string, Predicate>* objectPredicates;
    std::map<std::string, Action>* objectActions;
    //static std::map<std::string, std::function<bool(Object*,Object*,std::string)>> objectPredicates;
    static EventMgr* instance;
};

#endif // EVENTMGR_HPP
