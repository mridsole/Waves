#include "stdafx.h"
#include "SimNode.h"

using namespace hwsim;

SimNode::SimNode(SimNodeVertex* _vertex) :
	vertex(_vertex)
{

}


SimNode::~SimNode()
{
	// ummm
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
		
		// absorb less energy than injected (on the right side) = overheating!
		return wire->getHeatFuture()[1] + 1 * wire->config.dx;

		// fix derivative at 0 -> energy conservation
		//return wire->getHeatFuture()[1];
	} else {

		// try fixing the derivative at this end to 5 - energy injection??
		return wire->getHeatFuture()[wire->config.nx - 2] - 1 * wire->config.dx;

		// fix derivative at 0 -> energy conservation
		//return wire->getHeatFuture()[wire->_config.nx - 2];
	}
}