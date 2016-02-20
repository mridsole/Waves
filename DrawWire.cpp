#include "stdafx.h"

#include "DrawWire.h"

using namespace hwdraw;

DrawWire::DrawWire()
{
	// for now just test the line with some arbitrary values
	drawLine.thickness = 3.f;
	drawLine.startPos = sf::Vector2f(250, 250);
	drawLine.endPos = sf::Vector2f(400, 350);
	drawLine.color = sf::Color::Black;

	drawLine.makeLine();
}

// nothing here for now
DrawWire::~DrawWire() {}

void DrawWire::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	// draw the line
	target.draw(drawLine);
}
