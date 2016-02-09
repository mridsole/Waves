#pragma once

#include <utility>

#include "SimWire.h"

namespace hwsim {

// configuration options for nodes

// represents which end of the wire the node is connected to
enum class WireEnd { START, END };

// represents the type of node we're dealing with
enum class WaveNodeType { REFLECTING, INVERTING, ABSORBING };
enum class HeatNodeType { OPEN, CLOSED };

// class for the simulation representation of a node
// which is used for managing the heat and wave boundary
// conditions for wires
class SimNode
{

	friend class SimWire;
	friend class SimController;

private:

	SimNode();
	~SimNode();

public:

	// update the value at the boundary for all connected wires
	// must be called AFTER each wire has been updated!
	float waveBoundary(SimWire* wire, WireEnd wireEnd, float dt);
	float heatBoundary(SimWire* wire, WireEnd wireEnd, float dt);

	// add/remove wires from the node
	void addWire(SimWire* wire, WireEnd wireEnd);
	void removeWire(SimWire* wire, WireEnd wireEnd);

private:

	// vector of wires connected at the node, and how they're connected (which end)
	std::vector<std::pair<SimWire*, WireEnd>> _wires;
};

}