#pragma once

namespace sim {

// responsible for keeping track of all wires and nodes
// managing memory, calling update functions, etc
class SimulationManager
{
public:
	SimulationManager();
	~SimulationManager();
};

}