#include "../hpp/ui.hpp"

//using namespace UI;

void UI::Component::applyStyle(cssHandler& css)
{
    for(auto i = css.getStyle().begin();i!=css.getStyle().end();i++)
    {
        changeStyle(i->first,i->second);
    }
}

/*
void UI::Component::execute(std::string name, void* arg)
{
    if(functions.find(name)!=functions.end() && functions[name] != nullptr)
        functions[name](arg, this);
}
*/
/*
void UI::Component::bind(std::string id,
                         std::function<void(void* arg,UI::Component* pthis)> func)
{
    functions[id] = func;
}
*/

void UI::Component::execute(std::string name)
{
    if(functions.find(name)!=functions.end() && functions[name] != nullptr)
        (*(functions[name]))(this);
}

void UI::Component::bind(std::string id, Functor* func)
{
    functions[id] = func;
}

sf::Color UI::Style::getColor(std::string val)
{
    sf::Color ret;
    if(val == "null")
    {
        ret = sf::Color::Black;
        return ret;
    }
    unsigned char flags = 0;
    std::transform(val.begin(), val.end(), val.begin(),
        [](unsigned char c){ return std::tolower(c); });
    flags+=isHex(val);
    flags+=isHexA(val);
    flags+=isRGB(val);
    flags+=isRGBA(val);
    switch(flags)
    {
    case 1:
        {
            std::cout << "Hex_rgb" << std::endl;
            ret.r = hexToChar(val[1],val[2]);
            ret.g = hexToChar(val[3],val[4]);
            ret.b = hexToChar(val[5],val[6]);
            break;
        }
    case 2:
        {
            std::cout << "Hex_rgba" << std::endl;
            ret.r = hexToChar(val[1],val[2]);
            ret.g = hexToChar(val[3],val[4]);
            ret.b = hexToChar(val[5],val[6]);
            ret.a = hexToChar(val[7],val[8]);
            break;
        }
    case 4:
        {
            std::cout << "rgb" << std::endl;
            auto b = val.find("(");
            auto e = val.find(",");
            int r = std::stoi(val.substr(b+1,e-b-1));
            b = e+1;
            e = val.find(",",b);
            int g = std::stoi(val.substr(b,e-b));
            b = e+1;
            e = val.find(")",b);
            int bl = std::stoi(val.substr(b,e-b));
            ret.r = std::clamp(r,0,255);
            ret.g = std::clamp(g,0,255);
            ret.b = std::clamp(bl,0,255);
            break;
        }
    case 8:
        {
            std::cout << "rgba" << std::endl;
            auto b = val.find("(");
            auto e = val.find(",");
            int r = std::stoi(val.substr(b+1,e-b-1));
            b = e+1;
            e = val.find(",",b);
            int g = std::stoi(val.substr(b,e-b));
            b = e+1;
            e = val.find(",",b);
            int bl = std::stoi(val.substr(b,e-b));
            b = e+1;
            e = val.find(")",b);
            int a = 255*std::stof(val.substr(b,e-b));
            ret.r = std::clamp(r,0,255);
            ret.g = std::clamp(g,0,255);
            ret.b = std::clamp(bl,0,255);
            ret.a = std::clamp(a,0,255);
            break;
        }
    default:
        {
            ret = getColor(CssMgr::getColor(val)); //dangerous
        }
    }

    return ret;
}

unsigned char UI::Style::isHex(std::string val)
{
    std::regex reg(R"a(^#[a-f0-9]{6}$)a");
    return (std::regex_search(val,reg)?1:0);
}

unsigned char UI::Style::isHexA(std::string val)
{
    std::regex reg(R"a(^#[a-f0-9]{8}$)a");
    return (std::regex_search(val,reg)?2:0);
}

unsigned char UI::Style::isRGB(std::string val)
{
    std::regex reg(R"a(^rgb\((\s*\d{1,3}),(\s*\d{1,3}),(\s*\d{1,3})\)$)a");
    return (std::regex_search(val,reg)?4:0);
}

unsigned char UI::Style::isRGBA(std::string val)
{
    std::regex reg(R"a(^rgba\((\s*\d{1,3}),(\s*\d{1,3}),(\s*\d{1,3}),(\s*(1|0\.\d+))\s*\)$)a");
    return (std::regex_search(val,reg)?8:0);
}

unsigned char UI::Style::hexToChar(char a, char b)
{
    a = hexCharToNumber(a);
    b = hexCharToNumber(b);
    return a*16+b;
}

unsigned char UI::Style::hexCharToNumber(char a)
{
    if(a>='0'&&a<='9') a-='0';
    else if(a>='a'&&a<='f') a=a-'a'+9;
    else a=15;
    return a;
}

