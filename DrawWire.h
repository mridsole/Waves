#pragma once

#include "SFML/Graphics.hpp"

#include "sfLine.h"

namespace hwdraw
{

// responsible for drawing a game wire to the screen
class DrawWire : public sf::Drawable
{
public:

	DrawWire();
	~DrawWire();
	
	// satisfy drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	// the line used to draw this
	Line drawLine;
};

};
