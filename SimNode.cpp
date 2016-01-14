#include "stdafx.h"
#include "SimNode.h"

using namespace sim;

SimNode::SimNode()
{

}


SimNode::~SimNode()
{
	// copy the list of connected wires
	auto wireList = this->_wires;

	// remove all wires
	for (unsigned i = 0; i < wireList.size(); i++) {
		this->removeWire(wireList[i].first, wireList[i].second);
	}
}

float SimNode::waveBoundary(SimWire* wire, WireEnd wireEnd, float dt) {

	// for now
	if (wireEnd == WireEnd::START) {
		return 1.f;
	} else {
		return -1.f;
	}
}

float SimNode::heatBoundary(SimWire* wire, WireEnd wireEnd, float dt) {

	// for now
	if (wireEnd == WireEnd::START) {
		return 1.f;
	} else {

		// try fixing the derivative at this end to 5 - energy injection??
		return wire->getHeatFuture()[wire->_config.nx - 2] + 5 * wire->_config.dx;
	}
}

void SimNode::addWire(SimWire* wire, WireEnd wireEnd) {

	// first, check for a duplicate
	auto wireEndPair = std::pair<SimWire*, WireEnd>(wire, wireEnd);
	auto wireEndPairIt = std::find(this->_wires.begin(), this->_wires.end(), wireEndPair);

	// if the entry doesn't exist, make it
	if (wireEndPairIt == this->_wires.end()) {
		this->_wires.push_back(wireEndPair);
	}

	// set the appropriate value in the wire
	if (wireEnd == WireEnd::START) {
		wire->_bcNodeStart = this;
	} else if (wireEnd == WireEnd::END) {
		wire->_bcNodeEnd = this;
	}
}

void SimNode::removeWire(SimWire* wire, WireEnd wireEnd) {

	// find the iterator for it
	auto wireEndPair = std::pair<SimWire*, WireEnd>(wire, wireEnd);
	auto wireEndPairIt = std::find(this->_wires.begin(), this->_wires.end(), wireEndPair);

	if (wireEndPairIt != this->_wires.end()) {

		// remove it
		this->_wires.erase(wireEndPairIt);

		// remove references within the wire itself
		if (wireEnd == WireEnd::START) {
			wire->_bcNodeStart = nullptr;
		} else if (wireEnd == WireEnd::END) {
			wire->_bcNodeEnd = nullptr;
		}
	} else {

		// TODO: really should do something here - if someone's trying to remove
		// a wire-node link that doesn't exist, something is wrong
	}
}