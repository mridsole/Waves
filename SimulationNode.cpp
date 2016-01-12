#include "stdafx.h"
#include "SimulationNode.h"

using namespace sim;

SimulationNode::SimulationNode()
{
}


SimulationNode::~SimulationNode()
{
}

void SimulationNode::addWire(SimulationWire* wire, WireEnd wireEnd) {

	// first, check for a duplicate
	auto wireEndPair = std::pair<SimulationWire*, WireEnd>(wire, wireEnd);
	auto wireEndPairIt = std::find(this->wires.begin(), this->wires.end(), wireEndPair);

	// if the entry doesn't exist, make it
	if (wireEndPairIt == this->wires.end()) {
		this->wires.push_back(wireEndPair);
	}

	// set the appropriate value in the wire
	if (wireEnd == WireEnd::START) {
		wire->_bcNodeStart = this;
	} else if (wireEnd == WireEnd::END) {
		wire->_bcNodeEnd = this;
	}
}

void SimulationNode::removeWire(SimulationWire* wire, WireEnd wireEnd) {

	// find the iterator for it
	auto wireEndPair = std::pair<SimulationWire*, WireEnd>(wire, wireEnd);
	auto wireEndPairIt = std::find(this->wires.begin(), this->wires.end(), wireEndPair);

	if (wireEndPairIt != this->wires.end()) {

		// remove it
		this->wires.erase(wireEndPairIt);

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