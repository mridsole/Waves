#include "stdafx.h"
#include "stdio.h"
#include <functional>
#include "DrawWire.h"


using namespace hwdraw;

DrawWire::DrawWire(SelectionController& selCtrl, 
	FrameUpdateDispatcher& fUDispatch) :
	selMouseable(fUDispatch, *this),
	selectable(selCtrl, selMouseable)
{
	// for now just test the line with some arbitrary values
	drawLine.thickness = 3.f;
	drawLine.startPos = sf::Vector2f(250, 250);
	drawLine.endPos = sf::Vector2f(400, 350);
	drawLine.color = sf::Color::Black;

	drawLine.makeLine();

	// bind selectable events
	onSelectCallbackID = selectable.onSelect.addCallback(
		std::bind(&DrawWire::onSelect, this, std::placeholders::_1));

	onDeselectCallbackID = selectable.onDeselect.addCallback(
		std::bind(&DrawWire::onDeselect, this, std::placeholders::_1));
}

// nothing here for now
DrawWire::~DrawWire() {

	// unbind selectable events
	selectable.onSelect.removeCallbackByID(onSelectCallbackID);
	selectable.onDeselect.removeCallbackByID(onDeselectCallbackID);
}

void DrawWire::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	// draw the line
	target.draw(drawLine);
}

// TODO: decide on where to actually store these
sf::Vector2f DrawWire::getStartPos() const {
	return drawLine.startPos;
}

sf::Vector2f DrawWire::getEndPos() const {
	return drawLine.endPos;
}

void DrawWire::onSelect(const Selectable::Event& selEvent) {

	// change the wire to blue
	drawLine.color = sf::Color::Blue;
	drawLine.makeLine();
}

void DrawWire::onDeselect(const Selectable::Event& selEvent) {

	printf("Wire deselected!\n");

	// change the wire to black
	drawLine.color = sf::Color::Black;
}
