#pragma once

#include <utility>

#include "SimulationWire.h"

namespace sim {

// represents which end of the wire the node is connected to
enum class WireEnd { START, END };

// class for the simulation representation of a node
// which is used for managing the heat and wave boundary
// conditions for wires
class SimulationNode
{

	friend class SimulationWire;

public:

	SimulationNode();
	virtual ~SimulationNode() = 0;

	// update the value at the boundary for all connected wires
	// must be called AFTER each wire has been updated!
	virtual void updateWave(float dt) = 0;
	virtual void updateHeat(float dt) = 0;

	// add/remove wires from the node
	void addWire(SimulationWire*, WireEnd);
	void removeWire(SimulationWire*, WireEnd);

private:

	// vector of wires connected at the node, and how they're connected (which end)
	std::vector<std::pair<SimulationWire*, WireEnd>> wires;
};

}