#include "stdafx.h"
#include "SimInitializer.h"

using namespace hwsim;

SimInitializer::SimInitializer(SimController& simCtrl_) :
	simCtrl(simCtrl_)
{}


SimInitializer::~SimInitializer()
{
}

void SimInitializer::constructInitializeWire(SimWireEdge* edge) {

	constructWire(edge);
	initializeWire(edge);
}


// TODO: make this also add the created wire to the SimController list
void SimInitializer::constructWire(SimWireEdge* edge) {

	// if the edge is storing a nullptr then allocate a new wire first
	if (edge->getWire() == nullptr)
		edge->setWire(new SimWire(edge, simCtrl));
}

void SimInitializer::initializeWire(SimWireEdge* edge) {

	// make sure everything we need isn't null
	if (edge->getWire() == nullptr)
		return;

	// if the config/state pointers are null, then use their respective defaults
	// otherwise, use the custom provided 
	SimWire::Config& cfg = (edge->getWireConfig() == nullptr) ?
		defaultWireConfig : *edge->getWireConfig();

	SimWire::InitState& init = (edge->getInitState() == nullptr) ?
		defaultWireInitState : *edge->getInitState();

	// now initialize the wire - this is where most of the memory allocation actually happens
	edge->getWire()->initialize(cfg, init, simCtrl.config.dt);
}

void SimInitializer::constructInitializeNode(SimNodeVertex* vertex) {

	constructNode(vertex);
	initializeNode(vertex);
}

void SimInitializer::constructNode(SimNodeVertex* vertex) {

	if (vertex->getSimNode() == nullptr)
		vertex->setSimNode(new hwsim::SimNode(vertex));
}

// TODO: figure out exactly what should be done here
void SimInitializer::initializeNode(SimNodeVertex* vertex) {


}
