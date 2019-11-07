#ifndef CSSMGR_HPP
#define CSSMGR_HPP

#include "cssHandler.hpp"
#include <map>

namespace UI
{
    class CssMgr
    {
    public:
        CssMgr();
        ~CssMgr();
        void loadFromFile(std::string filename);
        cssHandler* getCss(std::string);
        static std::string getColor(std::string);
    private:
        std::map<std::string, cssHandler*> styles;
        static std::map<std::string, std::string> colors;
        std::map<std::string, std::string> loadColors(std::string);
        void parseCss(std::string);
        void seekNames(std::string text, cssHandler* css);
    };
}

#endif
