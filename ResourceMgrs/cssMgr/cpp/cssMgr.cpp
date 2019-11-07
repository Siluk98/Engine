#include "../hpp/cssMgr.hpp"
#include <fstream>
#include <regex>
#include <iostream>

using namespace UI;

std::map<std::string, std::string> CssMgr::colors;

CssMgr::CssMgr(){
    colors = loadColors("colors.txt");
    for(auto i : colors)
    {
        std::cout << i.first << ":" << i.second << std::endl;
    }
};
CssMgr::~CssMgr(){
    /*
    for(auto i = styles.begin();i!=styles.end();i++)
    {
        delete i->second;
    }
    styles.empty();
    */
};

void CssMgr::loadFromFile(std::string filename)
{
    std::ifstream file;
    file.open(filename);
    if(file.good())
    {
        std::string text{};

        while(!file.eof())
        {
            std::string line; // optimize
            std::getline(file,line);
            text += line+'\n';
        }
        //std::cout << text << std::endl;
        parseCss(text);
        std::cout << "File " << filename << " loaded" << std::endl;
    }
    else
    {
        std::cout << "File " << filename << " could not be opened" << std::endl;
    }
    file.close();
}

void updateCss(std::string s, cssHandler* css);
void CssMgr::parseCss(std::string text){

    std::regex prop(R"(.*(\n)*\{(.*(\n)*)*?\})");
    std::smatch m;
    //std::cout << "CHUJ" << std::endl;

    while(std::regex_search(text, m, prop))
    {
        //std::cout << __FILE__ << ":" << __LINE__ << ":m.str(): " << m.str() << std::endl;
        std::string s = m.str();
        text = m.suffix();
        std::regex names(R"(^(.)*(\n)*\{)");
        std::smatch n;
        if(std::regex_search(s,n,names))
        {
            cssHandler* css = new cssHandler;

            std::string s2 = n.str();
            seekNames(s2,css);

            std::string s3 = n.suffix();
            std::regex atribs(R"(.+\:.+)");
            std::smatch k;
            while(std::regex_search(s3, k, atribs))
            {
                //std::cout << "k.str(): " << k.str() << std::endl;
                std::string o = k.str();
                updateCss(o, css);
                s3 = k.suffix();
            }
        }
    }
}

static std::vector<std::string> split(std::string strToSplit, char delimeter);
static std::string cleanWord(std::string text);

void updateCss(std::string s, cssHandler* css)
{
    s = cleanWord(s);
    std::vector<std::string> v = split(s, ' ');
    for(unsigned int i=0;i<v.size();i++)
    {
        v[i] = cleanWord(v[i]);
    }
    if(v[1]==":" || v[1]=="") v.erase(v.begin()+1);
    if(v.size()!=2)
    {
        std::cout << "Style improper" << std::endl;
        return;
    }
    css->changeAttribute(v[0],v[1]);
}

void CssMgr::seekNames(std::string text, cssHandler* css)
{
    text = cleanWord(text);
    std::vector<std::string> names = split(text, ',');
    for(auto i: names)
    {
        //std::cout << "m: '" << i << "'" << std::endl;
        i = cleanWord(i);
        //std::cout << "n: '" << i << "'" << std::endl;
        //std::cout << "CLEAN: " << css << std::endl;
        //styles->insert_or_assign(i, css);
        styles[i]= css;
        //std::cout << "test" << std::endl;
        //std::cout << styles[i] << std::endl;
    }
}

cssHandler* CssMgr::getCss(std::string name)
{
    if(styles.find(name)!=styles.end())
        return styles.at(name);
    else
        return nullptr;
}

static std::vector<std::string> split(std::string strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
    {
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}

static std::string cleanWord(std::string text)
{
    while(text.back()==' ' ||
          text.back()=='\n' ||
          text.back()==':' ||
          text.back()=='{') text.pop_back();
    while(text.front()==' ' ||
          text.front()=='\n'||
          text.front()==':') text.erase(0,1);
    return text;
}

std::map<std::string, std::string> CssMgr::loadColors(std::string filename)
{
    std::map<std::string, std::string> ret;
    std::ifstream file(filename);
    if(!file.good())
    {
        std::cout << "Colors could not be loaded" << std::endl;
        return ret;
    }
    else
    {
        std::string name;
        std::string clr;
        std::string temp;
        while(!file.eof())
        {
            std::getline(file, temp);
            auto it = temp.find(" ");
            name = temp.substr(0,it);
            clr = "#";
            clr += temp.substr(it+1);
            std::transform(name.begin(), name.end(), name.begin(),
                [](unsigned char c){ return std::tolower(c); });
            ret[name] = clr;
        }
        return ret;
    }
    file.close();
}

std::string CssMgr::getColor(std::string name)
{
    if(colors.find(name)!= colors.end())
    return colors[name];
    else return "null";
}
