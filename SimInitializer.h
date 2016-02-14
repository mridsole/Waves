#pragma once

#include "SimWire.h"
#include "SimNode.h"
#include "SimGraphInterface.h"

namespace hwsim {

// utility class for constructing and initializing SimWire objects
// based on provided default configurations and states
class SimInitializer
{

public:

	SimInitializer();
	SimInitializer(float dt);
	~SimInitializer();

	void constructInitializeWire(SimWireEdge* edge);
	void constructWire(SimWireEdge* edge);
	void initializeWire(SimWireEdge* edge);

	void constructInitializeNode(SimNodeVertex* vertex);
	void constructNode(SimNodeVertex* vertex);
	void initializeNode(SimNodeVertex* vertex);

	SimWire::Config defaultWireConfig;
	SimWire::InitState defaultWireInitState;

	// the timestep to use when applying the velocity in initialization
	// this seems to be something of an odd one out, not sure where else to put it
	float dt;
};

};