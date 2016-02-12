#include "stdafx.h"
#include "SimConstructor.h"

using namespace hwsim;

SimConstructor::SimConstructor()
{
}


SimConstructor::~SimConstructor()
{
}

void SimConstructor::constructWire(SimWireEdge* edge) {

	// if the edge is storing a nullptr then allocate a new wire first
	if (edge->getWire() == nullptr)
		edge->setWire(new SimWire());

	// if the config/state pointers are null, then use their respective defaults
	// otherwise, use the custom provided 
	SimWire::Config& cfg = (edge->getWireConfig() == nullptr) ? 
		defaultWireConfig : *edge->getWireConfig();

	SimWire::InitState& init = (edge->getInitState() == nullptr) ?
		defaultWireInitState : *edge->getInitState();

	// now initialize the wire - this is where most of the memory allocation actually happens
	//edge->getWire()->initialize();
}

void SimConstructor::initializeWire(SimWireEdge* edge) {


}