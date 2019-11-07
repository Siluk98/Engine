#include "../hpp/range.hpp"
#include "../../ResourceMgrs/cssMgr/hpp/cssHandler.hpp"
#include <iostream>
#include "../../ResourceMgrs/stateMgr/hpp/state.hpp"
#include "../../Core/hpp/engine.hpp"
#include "../../ResourceMgrs/eventMgr/hpp/event.hpp"

UI::Range::Range(std::string id, cssHandler& css)
{

}

UI::Range::Range(std::string id, cssHandler* css)
{

}

UI::Range::~Range()
{

}

void UI::Range::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(*field);
    target.draw(*slider);
}

void UI::Range::update()
{

}

std::string UI::Range::create(std::string obj, std::string params)
{
    return "What's that?";
}

void UI::Range::changeStyle(std::string atr, std::string val)
{

}
