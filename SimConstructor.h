#pragma once

#include "SimWire.h"
#include "SimNode.h"
#include "SimGraphInterface.h"

namespace hwsim {

// utility class for constructing and initializing SimWire objects
// based on provided default configurations and states
class SimConstructor
{

public:

	SimConstructor();
	~SimConstructor();

	void constructWire(SimWireEdge* edge);
	void initializeWire(SimWireEdge* edge);

	SimWire::Config defaultWireConfig;
	SimWire::InitState defaultWireInitState;
};

};