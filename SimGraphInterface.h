#pragma once

#include <vector>

namespace hwsim {

class SimWire;
class SimNode;

struct SimWireEdge;
struct SimNodeVertex;

// Interfaces for SimWire and SimNode to use, in order to access the graph model
// the data fields of a DirectedGraph<> Edge/Vertex specialization should implement these

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
	virtual SimNode* getSimNode() = 0;
};

};