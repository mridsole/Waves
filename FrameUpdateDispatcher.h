#pragma once

#include "EventDispatcher.h"

#include <SFML/Graphics.hpp>

namespace hwgame {

// can add other info to this as appropriate (such as frame dt etc)
struct FrameUpdateEvent {

	std::vector<sf::Event> sfEvents;
};

typedef EventDispatcher<const FrameUpdateEvent&> FrameUpdateDispatcher;

};