#pragma once

#include "SimWire.h"
#include "SimNode.h"
#include "DirectedGraph.h"

namespace hwgame {
	
// funky forward decl stuff
struct CircuitEdgeData;
struct CircuitVertexData;

using CircuitEdge = dirgraph::Edge<CircuitEdgeData, CircuitVertexData>;
using CircuitVertex = dirgraph::Vertex<CircuitEdgeData, CircuitVertexData>;

// CircuitEdgeData and CircuitVertexData inherit a type parameterised by themselves - nice
// actually this is just a case of the curiously recurring template pattern
using CircuitEdgeDataBase = dirgraph::EdgeData<CircuitEdgeData, CircuitVertexData>;
using CircuitVertexDataBase = dirgraph::VertexData<CircuitEdgeData, CircuitVertexData>;

struct CircuitEdgeData : public CircuitEdgeDataBase, public hwsim::SimWireEdge
{
	// the simulation data for this wire
	hwsim::SimWire* simWire;

	CircuitEdgeData(CircuitEdge* _thisEdge) :
		CircuitEdgeDataBase::EdgeData(_thisEdge)
	{};

	// satisfy SimWireEdge
	hwsim::SimNodeVertex& getStartNode();
	hwsim::SimNodeVertex& getEndNode();
	hwsim::SimWire* getSimWire();
};

struct CircuitVertexData : public CircuitVertexDataBase, public hwsim::SimNodeVertex
{
	CircuitVertexData(CircuitVertex* _thisVertex) :
		CircuitVertexDataBase::VertexData(_thisVertex)
	{};

	// satisfy SimNodeVertex
	virtual Edges& getEdges();

private:

	// getEdges implementation
	Edges edgesBuffer;
};

};