#pragma once

#include "SimWire.h"
#include "SimNode.h"

namespace hwsim {

struct SimWireEdge;
struct SimNodeVertex;

// the graph interface
struct SimWireEdge
{
	SimWireEdge() {};
	virtual ~SimWireEdge() {};

	virtual SimNodeVertex& getStartNode() = 0;
	virtual SimNodeVertex& getEndNode() = 0;
	virtual SimWire* getSimWire() = 0;
};

struct SimNodeVertex
{
	using Edges = std::vector<SimWireEdge*>;

	SimNodeVertex() {};
	virtual ~SimNodeVertex() {};

	virtual Edges& getEdges() = 0;
};

};