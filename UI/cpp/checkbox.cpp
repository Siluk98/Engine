#include <iostream>
#include "../../ResourceMgrs/stateMgr/hpp/state.hpp"
#include "../../Core/hpp/engine.hpp"
#include "../../ResourceMgrs/eventMgr/hpp/event.hpp"
#include "../hpp/checkbox.hpp"

UI::Checkbox::Checkbox(std::string _id, cssHandler& css)
{
    std::cout << "chkbox" << std::endl;
    id = _id;
    /*
    bind("click", [](void* arg, Component* pthis){
        UI::Checkbox* ptr = dynamic_cast<Checkbox*>(pthis);
        ptr->flipValue();
         });
    */
    Functor *func = new Functor(nullptr,[](void* arg, Object* pthis){
        UI::Checkbox* ptr = dynamic_cast<Checkbox*>(pthis);
        ptr->flipValue();
         });
    bind("Flip", func);
    //implement css
    outerWidth = 16;
    outerHeight = 16;
    innerWidth = outerWidth-8;
    innerHeight = outerHeight-8;

    value = 0;

    outer = sf::RectangleShape(sf::Vector2f(outerWidth,outerHeight));
    inner = sf::RectangleShape(sf::Vector2f(innerWidth,innerHeight));
    hitbox = new sf::IntRect(0,0,outerWidth,outerHeight);

    innerColor = sf::Color(0,0,0,0);
    outerColor = sf::Color::White;
    moveTo(100,100);

    applyStyle(css);

    outer.setFillColor(innerColor);
    outer.setOutlineColor(outerColor);
    outer.setOutlineThickness(-2);
    inner.setFillColor(outerColor);
    inner.setFillColor(outerColor);

    std::cout << "hitbox: " << hitbox->left << " " << hitbox->top << std::endl;
    isPressed = false;



    addType("checkbox");
    addEvent("MouseDown", Action{[](Object* a, Object* b, std::string arg1, std::string arg2){
                UI::Checkbox *c = dynamic_cast<Checkbox*>(a);
                c->isPressed = true;
                //std::cout << "check" << std::endl;
             }});
    addEvent("MouseUp", Action{[](Object* a, Object* b, std::string arg1, std::string arg2){
                    UI::Checkbox *c = dynamic_cast<Checkbox*>(a);
                    if(c->isPressed)
                    {
                        std::cout << "click " << c->id << std::endl;
                        c->isPressed = false;
                        c->execute("Flip");
                        c->execute("onInput");
                    }
             }});
}

UI::Checkbox::Checkbox(std::string id, cssHandler* css)
: UI::Checkbox(id,*css){}

UI::Checkbox::~Checkbox()
{
    for(std::pair<std::string,Functor*> i: functions)
    {
        delete i.second;
    }
}

void UI::Checkbox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(outer);
    if(value)
        target.draw(inner);
}

void UI::Checkbox::update()
{
    for(unsigned int i=0;i<events.size();i++)
    {
        events[i]->handle(this,nullptr,"","");
    }
}

std::string UI::Checkbox::create(std::string obj, std::string params)
{
    return "What's that?";
}

void UI::Checkbox::changeStyle(std::string atr, std::string val)
{
    try
    {
        if(val == "") return;
        std::cout << id << ": " << atr << ": " << val << std::endl;
        if(atr == "width")
        {
            int i = std::stoi(val);
            outerWidth = i;
            innerWidth = i-8;
            hitbox->width = outerWidth;
            outer.setSize(sf::Vector2f(outerWidth,outerHeight));
            inner.setSize(sf::Vector2f(innerWidth,innerHeight));
        }
        if(atr == "height")
        {
            int i = std::stoi(val);
            outerHeight = i;
            innerHeight = i-8;
            hitbox->height = outerHeight;
            outer.setSize(sf::Vector2f(outerWidth,outerHeight));
            inner.setSize(sf::Vector2f(innerWidth,innerHeight));

        }
        if(atr == "top")
        {
            int i = std::stoi(val);
            moveTo(hitbox->left,i);
        }
        if(atr == "left")
        {
            int i = std::stoi(val);
            moveTo(i,hitbox->top);
        }
        if(atr == "innerColor")
        {
            innerColor = UI::Style::getColor(val);
        }
        if(atr == "outerColor")
        {
            outerColor = UI::Style::getColor(val);
        }
    }
    catch(...)
    {
        std::cout << "Broken css" << std::endl;
    }
}

bool UI::Checkbox::getValue()
{
    return value;
}

bool UI::Checkbox::setValue(bool v)
{
   value = v;
   return value;
}

bool UI::Checkbox::flipValue()
{
    value = !value;
    std::cout << "value: " << value << std::endl;
    return value;
}

sf::Vector2f UI::Checkbox::moveTo(int x,int y)
{
    int dw = (outerWidth-innerWidth)/2;
    int dh = (outerHeight-innerHeight)/2;
    inner.setPosition(x,y);
    outer.setPosition(x-dw,y-dh);
    return Object::moveTo(x,y);
}
