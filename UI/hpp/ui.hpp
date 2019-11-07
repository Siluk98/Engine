#ifndef UI_HPP
#define UI_HPP

#include "style.hpp"
#include "../../ResourceMgrs/cssMgr/hpp/cssHandler.hpp"
#include "../../ResourceMgrs/cssMgr/hpp/cssMgr.hpp"
#include "../../Core/hpp/object.hpp"
#include "../../Core/hpp/functor.hpp"
#include <functional>
#include <regex>
#include <algorithm>
#include <cctype>
#include <string>
#include <iostream>

namespace UI
{
    namespace Style
    {
        sf::Color getColor(std::string val);
        unsigned char isHex(std::string val);
        unsigned char isHexA(std::string val);
        unsigned char isRGB(std::string val);
        unsigned char isRGBA(std::string val);
        unsigned char hexToChar(char a, char b);
        unsigned char hexCharToNumber(char a);
        enum class BoxSizing{ContentBox,BorderBox,PaddingBox};
    }

    class Component :public Object
    {
    public:
        virtual void update() = 0;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
        virtual void collide(Object*) = 0;
        virtual ~Component(){};
        virtual std::string create(std::string obj, std::string params) = 0;
        virtual void changeStyle(std::string atr, std::string val) = 0;
        void applyStyle(cssHandler& css);
        //std::map<std::string, std::function<void(void*,Component* pthis)>> functions;
        std::map<std::string, Functor*> functions;
        //void execute(std::string name, void* arg);
        void execute(std::string name);
        //void bind(std::string id, std::function<void(void*, Component* pthis)> fun);
        void bind(std::string id, Functor* fun);
    private:
    };
}

#include "range.hpp"
#include "button.hpp"
#include "canvas.hpp"

#endif
