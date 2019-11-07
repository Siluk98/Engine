#include "../hpp/progressBar.hpp"
#include "../../ResourceMgrs/fontMgr/hpp/fontMgr.hpp"
#include <iostream>

using namespace UI;

ProgressBar::ProgressBar(std::string _id, cssHandler* _css)
: ProgressBar(_id,*_css){}

ProgressBar::ProgressBar(std::string _id, cssHandler& _css)
{

    id = _id;
    fontName = "fonts/arial.ttf";

    width = 256;
    height = 16;
    borderThickness = 4;

    currentVal = 100;
    maxVal = 100;

    outer = sf::RectangleShape(sf::Vector2f(width,height));
    inner = sf::RectangleShape(sf::Vector2f(width,height));
    hitbox = new sf::IntRect(0,0,width+2*borderThickness,height+2*borderThickness);


    innerColor = sf::Color::Green;
    outerColor = sf::Color::Red;
    textColor = sf::Color::Black;
    displayStyle = Style::PBDisplayStyle::Normal;
    boxSizing = Style::BoxSizing::ContentBox;

    text.setCharacterSize(height);
    text.setFillColor(textColor);

    moveTo(100,100);

    applyStyle(_css);

    font = FontMgr::getInstance()->loadFont(fontName);
    text.setFont(*font);
}

ProgressBar::~ProgressBar()
{

}

void ProgressBar::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(border);
    target.draw(outer);
    target.draw(inner);
    target.draw(text);
}

void ProgressBar::update()
{
    std::string s = "";
    switch(displayStyle)
    {
    case Style::PBDisplayStyle::Normal:
        {
            s = std::to_string(currentVal);
            s += "/";
            s += std::to_string(maxVal);
            break;
        }
    case Style::PBDisplayStyle::Factor:
        {
            if(maxVal==0) s = "Max: 0";
            else s = std::to_string(currentVal/maxVal);
            break;
        }
    case Style::PBDisplayStyle::Percentage:
        {
            if(maxVal==0) s = "Max: 0";
            else s = std::to_string(currentVal/maxVal*100);
            s+="%";
            break;
        }
    case Style::PBDisplayStyle::None:
        {
            s="";
            break;
        }
    }
    //std::cout << "s: " << s << std::endl;
    text.setString(s);
    inner.setSize(sf::Vector2f(width*currentVal/maxVal,height));
}

void ProgressBar::changeStyle(std::string atr,std::string val)
{
    try
    {
        if(val == "") return;
        std::cout << id << ": " << atr << ": " << val << std::endl;
        if(atr == "width")
        {
            int i = std::stoi(val);
            width = i;
            reinterpretSize();
        }
        if(atr == "height")
        {
            int i = std::stoi(val);
            height = i;
            reinterpretSize();
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
            innerColor = Style::getColor(val);
            inner.setFillColor(innerColor);
        }
        if(atr == "outerColor")
        {
            outerColor = Style::getColor(val);
            outer.setFillColor(outerColor);
        }
        if(atr == "borderColor")
        {
            borderColor = Style::getColor(val);
            border.setFillColor(borderColor);
        }
        if(atr == "textColor")
        {
            textColor = Style::getColor(val);
            text.setFillColor(textColor);
        }
        if(atr == "borderThickness")
        {
            int i = std::stoi(val);
            borderThickness = i;
            reinterpretSize();
        }
        if(atr == "displayStyle")
        {
            std::transform(val.begin(), val.end(), val.begin(),
                [](unsigned char c){ return std::tolower(c); });
            if(val == "normal") displayStyle = Style::PBDisplayStyle::Normal;
            else if(val == "factor") displayStyle = Style::PBDisplayStyle::Factor;
            else if(val == "percentage") displayStyle = Style::PBDisplayStyle::Percentage;
            else if(val == "none") displayStyle = Style::PBDisplayStyle::None;
        }
        if(atr == "boxSizing")
        {
            std::transform(val.begin(), val.end(), val.begin(),
                [](unsigned char c){ return std::tolower(c); });
            if(val == "contentbox") boxSizing = Style::BoxSizing::ContentBox;
            else if(val == "borderbox") boxSizing = Style::BoxSizing::BorderBox;
            else if(val == "paddingbox") boxSizing = Style::BoxSizing::PaddingBox;
        }
        if(atr == "font-family")
        {
            fontName = "fonts/";
            fontName += val;
            fontName += ".ttf";
        }
    }
    catch(...)
    {
        std::cout << "Broken css" << std::endl;
    }
}

std::string ProgressBar::create(std::string obj, std::string params){return id;}

int ProgressBar::getMaxVal(){return maxVal;}
int ProgressBar::getVal(){return currentVal;}
int ProgressBar::setVal(int arg){
        currentVal = arg;
        return currentVal;
    }
int ProgressBar::setMaxVal(int arg){
        maxVal = arg;
        return maxVal;
    }
int ProgressBar::addVal(int arg)
{
    currentVal+=arg;
    return currentVal;
}

sf::Vector2f ProgressBar::moveTo(int x,int y)
{
    if(boxSizing == Style::BoxSizing::PaddingBox)
        boxSizing = Style::BoxSizing::ContentBox;
        //to be implemented
    if(boxSizing == Style::BoxSizing::ContentBox)
    {
        border.setPosition(x-borderThickness,y-borderThickness);
        inner.setPosition(x,y);
        outer.setPosition(x,y);
        text.setPosition(x+1,y);
    }
    else if(boxSizing == Style::BoxSizing::BorderBox)
    {
        border.setPosition(x,y);
        inner.setPosition(x+borderThickness,y+borderThickness);
        outer.setPosition(x+borderThickness,y+borderThickness);
        text.setPosition(x+borderThickness+1,y+borderThickness);
    }
    return Object::moveTo(x,y);
}

void ProgressBar::reinterpretSize()
{
    border.setSize(sf::Vector2f(width+2*borderThickness,height+2*borderThickness));
    outer.setSize(sf::Vector2f(width,height));
    inner.setSize(sf::Vector2f(width*currentVal/maxVal,height));
}
