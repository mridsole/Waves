#pragma once

#include "SimWire.h"

namespace hwsim {

// forward declarations of graph interface
struct SimWireEdge;
struct SimNodeVertex;

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

public:
	
	SimNode();
	~SimNode();

	// update the value at the boundary for all connected wires
	// must be called AFTER each wire has been updated!
	float waveBoundary(SimWire* wire, WireEnd wireEnd, float dt);
	float heatBoundary(SimWire* wire, WireEnd wireEnd, float dt);

	// interface into the graph structure
	SimNodeVertex* vertex;
};

};