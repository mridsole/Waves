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
	// the drawline defaults
	drawLine.thickness = 3.f;
	drawLine.color = sf::Color::Black;
	drawLine.makeLine();

	selectedDrawLine.thickness = drawLine.thickness * 3;
	selectedDrawLine.color = sf::Color(100, 100, 255, 100);

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

	// if our line is selected then draw the selection indicator
	if(selectable.state == Selectable::State::SELECTED)
		target.draw(selectedDrawLine);

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

void DrawWire::setStartPos(sf::Vector2f pos) {
	
	drawLine.startPos = pos;
	drawLine.makeLine();

	// match the select line
	selectedDrawLine.startPos = pos;
	selectedDrawLine.makeLine();
}

void DrawWire::setEndPos(sf::Vector2f pos) {
	
	drawLine.endPos = pos;
	drawLine.makeLine();

	selectedDrawLine.endPos = pos;
	selectedDrawLine.makeLine();
}

void DrawWire::onSelect(const Selectable::Event& selEvent) {

	// change the wire to blue
//	drawLine.color = sf::Color::Blue;
//	drawLine.makeLine();
}

void DrawWire::onDeselect(const Selectable::Event& selEvent) {

	printf("Wire deselected!\n");

	// change the wire to black
//	drawLine.color = sf::Color::Black;
//	drawLine.makeLine();
}
