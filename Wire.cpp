#include "stdafx.h"
#include "Wire.h"

#include "stdio.h"

using namespace hwgame;


void WireRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const {


}


WireUserInputHandler::WireUserInputHandler(
	FrameUpdateDispatcher& _frameUpdateDispatcher)
	:
	frameUpdateDispatcher(_frameUpdateDispatcher)
{
	// add our callback
	onFrameUpdateEventCallbackID = frameUpdateDispatcher.addCallback(std::bind(
		&WireUserInputHandler::onFrameUpdateEvent, *this, std::placeholders::_1));
}

WireUserInputHandler::~WireUserInputHandler() {

	// remove our callback
	frameUpdateDispatcher.removeCallbackByID(onFrameUpdateEventCallbackID);
}

void WireUserInputHandler::onFrameUpdateEvent(const FrameUpdateEvent& frameUpdateEvent) {

	// TODO: check for things like mouse over, clicking, etc
}


Wire::Wire(FrameUpdateDispatcher& frameUpdateDispatcher):
	wireRenderer(),
	userInputHandler(frameUpdateDispatcher),
	startNode(nullptr),
	endNode(nullptr),
	simWire(nullptr)
{}


Wire::~Wire()
{}

void Wire::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	
	this->wireRenderer.draw(target, states);
}