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
	// some testing data
	float x;
	float y;

	// the simulation data for this wire
	hwsim::SimWire* simWire;

	CircuitEdgeData(CircuitEdge* _thisEdge, float _x, float _y) :
		CircuitEdgeDataBase::EdgeData(_thisEdge),
		x(_x), y(_y)
	{};

	// satisfy SimWireEdge
	hwsim::SimNodeVertex& getStartNode() { return edge->startVertex.data; };
	hwsim::SimNodeVertex& getEndNode() { return edge->endVertex.data; };
	hwsim::SimWire* getSimWire() { return simWire; };
};

struct CircuitVertexData : public CircuitVertexDataBase, public hwsim::SimNodeVertex
{
	float z;

	CircuitVertexData(CircuitVertex* _thisVertex, float _z) :
		CircuitVertexDataBase::VertexData(_thisVertex),
		z(_z)
	{};

	// satisfy SimNodeVertex
	virtual Edges& edges() {

		// we have an std::vector<Node*>
		
		edgesBuffer.resize(0);
		for (auto it = vertex->edges.begin(); it < vertex->edges.end(); it++) {
			edgesBuffer.push_back(&((*it)->data));
		}

		return edgesBuffer;
	};

private:

	Edges edgesBuffer;
};

};